===================================
Honeynet Project Forensic Challenge
===================================

This repository mirrors and repackages the original data and analyses
from the Honeynet Project `Forensic Challenge`_.  The original web site
can be found at 
Python CLI for managing secrets (passwords, API keys, etc)

Directories and files
~~~~~~~~~~~~~~~~~~~~~

You can find BZ2 compressed partition images in the ``partition-images/``
directory.

Results from the reference analysis by David Dittrich for the Honeynet
Project and all 13 contestants are found in the ``results/`` directory.

The file ``timestamp.txt`` is the original timestamped file with
MD5 hashes of the original images, for "chain of custody" style
integrity validation.  As the new files are now compressed with
a different algorithm, the old ``.gz`` MD5 hashes are useless,
but the uncompressed files should still hash the same.

Credits
---------

The original Honeynet Project `Forensic Challenge`_ web site
is http://old.honeynet.org/challenge/

.. _Forensic Challenge: http://old.honeynet.org/challenge/
