Frequently Asked Questions about The Forensic Challenge
=======================================================

<center>
<BR>
<img src="../images/forensic.gif" alt="Forensic Challenge"><BR>
<img src="../images/faq.gif" alt="FAQ">
</center>
<hr>

In order to maintain sanity and control of time, the most frequently
asked questions about The Honeynet Project's Forensic Challenge
are found here.  I hope the answer you're looking for is included.

Dave Dittrich

QUESTIONS
---------

Why are you sponsoring the Forensic Challenge?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


There are several answers to this question.

* Because one thing the Honeynet Project is not short of is compromised systems.

* Because not everybody can (or should) set up their own honeypots.

* Because nobody has ever done anything like this, and people on
  various lists have asked for "in the wild" compromised disc images
  to practice on.

* Because I've done several detailed analyses of compromised systems,
  but because of the nature of the incidents have never been able to fully
  disclose the contents of the compromised system's file system or release
  complete details about the incident.  With this system, there are no such
  privacy or confidentiality concerns.


How did you think of doing this?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The idea (despite Lance's insistence otherwise; I have the {black|e}mail to
prove it!) came from the Honeynet Project's founder, Lance Spitzner, as a
result of the Honeynet Project members' shifting focus from external data
(e.g., IDS logs) to local data on the file system itself.

Several members, such as myself, Kevin Mandia, and Lance, had been using The
Coroner's Toolkit on Linux and Solaris systems to analyze compromised systems
and reconstruct events using information remaining on the system.  Kind of like
examining a crime scene looking for fingerprints, hair samples, splatters and
spills, overturned furniture, broken windows, etc., and trying to reconstruct
what caused all those things to be in the state they were found.

The idea of The Forensic Challenge was to open this learning process up to the
security community at large and allow everyone to benefit from the experiment.

How did you make images of the compromised system?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The indvidual disk partition images were taken from each of the systems'
active partitions at the time of compromise. It was created 08 November,
2000, at 21:00 CST.  The following process was used to take the images,
with minimum data pollution as a primary goal.  We did not take the system down
during the process.  The following actions were taken while the system
was still live.

* Mounted CDROM containing forensic analysis tools (all statically compiled).

* Used static binaries of ``dd(1M)`` and ``netcat(1M)`` from the CDROM to
  ``dd`` images of the hard drive to a trusted forensic system over the network.
  This is done by the following:

  **Trusted System**:  Initiate a listening daemon on port 10000 of the trusted
  system using netcat:

  .. code-block:: shell

      # nc -l -p 10000 > honeypot.hda8.dd

  **Compromised System**: Copied the each partition of the hard drive using
  ``dd(1)``, then piped the ``dd`` images of the drive over the network to
  the trusted system (``192.168.1.1``) listening on port ``10000``:

  .. code-block:: shell

      # /cdrom/dd bs=1024 < /dev/hda8 | /cdrom/nc 192.168.1.1 10000 -w 3

  ..

  This process was repeated for every partition on the hard drive, including
  swap.  We now had a image of every partition on the trusted forensic system.
  MD5 checksums were produced at this time to compare against subsequent copies.
  These images were then combined into a single  for ease of transmission, which
  was also checksummed for the same reason.

Note that using this method does not allow a direct comparison against
the original partition contents on the hard drive, since the system
(continuing to run) would constantly change bits in the file system
as programs are run, buffers flushed, etc.  If you are imaging a
system for possible prosecution, you may wish to use a different
procedure that supports a more clear chain of custody for the bits
on the drive.  The Honeynet Project chose this method as it allowed the
blackhat to return in the future and we could continue our surveillance and
information gathering.

I noticed XYZ on the system.  Can you confirm that you did this, and not the intruder?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

No.  You have all the clues we're going to give you.

Part of the challenge in forensic analysis is identifying questions like this
yourself -- devloping hypotheses -- and then finding evidence to allow you to
determine whether your hypothesis is probable (a theory) or not.  The more
supporting evidence you can find, the greater the likelihood your theory is
correct.  Sometimes you find evidence that doesn't fit your hypothesis, and it
leads you to a new one, or to a brief *AHA!!!* moment of enlightenment.

Also, in a real world investigation, you may not have the luxury of
interviewing the system administrator.  They may have left the company.  You
must take your understanding of how Unix (Linux) works, how timestamps are
used, look for alternative sources of data, etc.  Go re-read the
`Challenge web page<../>`__ for references to help you with this process.
