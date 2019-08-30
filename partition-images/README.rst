.. image:: ../images/page_titles_for_challenge_i.jpg

Honeypot Disk Partition Images
==============================

Original partitioning layout
----------------------------

The original disk partition layout of the honeypot was:

.. code-block:: shell

    /dev/hda8       /
    /dev/hda1       /boot
    /dev/hda6       /home
    /dev/hda5       /usr
    /dev/hda7       /var
    /dev/hda9       swap

..

The MD5 hashes of the raw partition images (also in ``md5sums.txt``) are:

.. code-block:: shell

   $ md5sum *.dd
   a1dd64dea2ed889e61f19bab154673ab  honeypot.hda1.dd
   c1e1b0dc502173ff5609244e3ce8646b  honeypot.hda5.dd
   4a20a173a82eb76546a7806ebf8a78a6  honeypot.hda6.dd
   1b672df23d3af577975809ad4f08c49d  honeypot.hda7.dd
   8f244a87b8d38d06603396810a91c43b  honeypot.hda8.dd
   b763a14d2c724e23ebb5354a27624f5f  honeypot.hda9.dd

..

The MD5 hashes of the compressed files (also in ``md5sums-bz2.txt``) are:

.. code-block:: shell

    $ md5sum *.dd.bz*
    212fbb36529b8b5c12a27f7eace520e7  honeypot.hda1.dd.bz2
    ed9909834efe9f9f5d0726df8ee02e3a  honeypot.hda5.dd.bz2.aa
    779460c0dddc28f0f78a39c7e9e4e083  honeypot.hda5.dd.bz2.ab
    c7f824bf554a9a0731865a3a4eb3cc76  honeypot.hda6.dd.bz2
    06dde9c66c13cbed35d475d8eefd397b  honeypot.hda7.dd.bz2
    f2dab4da06b21443edf0f56f64d15f5a  honeypot.hda8.dd.bz2
    70db9910072e4cc2846191ad3761eb5a  honeypot.hda9.dd.bz2

..

Compressed images
-----------------

The original Honeynet Project web site had disk images compressed
with ``gzip``. This repository uses the more efficient
BZ2 compression algorithm to get the repository site as
small as possible.

GitHub has a strict maximium per-file limit of 100MB. The
``hda5`` partition, uncompressed, is 1.2GB. Even when compressed
with BZ2 at the maximum compression level, the resulting file only
gets down to 128MB, which is too large.

To get around this limit, the BZ2 compressed file contents are
split (using, yes, ``split``) into two parts:

.. code-block:: shell

    $ md5sum honeypot.hda5.dd
    c1e1b0dc502173ff5609244e3ce8646b  honeypot.hda5.dd
    $ bzip2 -c honeypot.hda5.dd | split -b 90m - honeypot.hda5.dd.bz2.
    $ du -sh honeypot.hda5.dd.a[ab]
    97M     honeypot.hda5.dd.bz2.aa
    28M     honeypot.hda5.dd.bz2.ab

..

To get back to one file, simply concatenate those two files in
alphabetic order, while ``bzunzip2`` decompressing standard
input and redirecting standard output to ``honeypot.hda5.dd``,
like this:

.. code-block:: shell

    $ cat honeypot.hda5.dd.bz2.a[a]b | bunzip2 -c > honeypot.hda5.dd

..

To prove this results in the same original file, compare the
hash:

.. code-block:: shell

    $ cat honeypot.hda5.dd.bz2.a[a]b | bunzip2 -c | md5sum
    c1e1b0dc502173ff5609244e3ce8646b  -

..

.. EOF
