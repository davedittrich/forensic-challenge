#!/bin/bash

DIR=${1:-forensic-challenge}
CWD=$(pwd)
IMG=partition-images
REPO=https://github.com/davedittrich/forensic-challenge.git

if [ -z "$DIR" ]; then
    echo 'Usage: $0 directory'
    exit 1
fi


if [[ "$CWD" == *"$DIR"* ]]; then
    echo "[-] \"DIR\" can't be part of \"$CWD\""
    exit 1
fi

AVAILABLE=$(df -k  --output=avail "$(dirname $DIR)" | tail -1)
# Slightly conservative estimate of max file space.
NEEDED=3250000

if [ $NEEDED -gt $AVAILABLE ]; then
    echo "[-] Need $NEEDED blocks, but only $AVAILABLE available: aborting."
    exit 1
fi

# Ensure directory exists
if [ ! -d "$DIR" ]; then
    echo '[+] Creating directory' "$DIR"
    mkdir -p "$DIR"
else
    echo '[-] Directory '"$DIR"' already exists: aborting.'
    exit 1
fi

cd "$DIR"
echo "[+] Sparse cloning repo $REPO"
git init 2>&1 >/dev/null
git remote add origin -f "$REPO"
git config core.sparsecheckout true
echo "$IMG" > .git/info/sparse-checkout
git pull origin master

echo '[+] Decompressing partition images:'
for F in "$IMG"/honeypot.hda[0-9].dd.bz2; do
    echo -n "[+]   $(basename $F)..."
    bunzip2 -c "$F" > "$(basename $F .bz2)"
    echo "done."
    rm "$F"
done
echo -n "[+]   honeypot.hda5.dd.bz2..."
cat "$IMG"/honeypot.hda5.dd.bz2.a[ab] |
    bunzip2 -c > honeypot.hda5.dd
echo "done."

echo '[+] Verifying integrity of decompressed files in '"$DIR"':'
md5sum -c "$IMG/md5sums.txt"

rm -rf ./"$IMG"/ .git

exit $?

# vim: set ts=4 sw=4 tw=0 et :
