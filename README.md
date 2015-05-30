# FreeDCM

This wants to be a clean and easy to port implementation of the DCM algortihm.

There are many libraries out there, but this implementation as some great differences:
- removed foregn code (ofted they they bumdled with a processing interface)
- removed sensors code, and any dependecy on it
- as portable as possibe
- "drop in" as git submodule/subtree is easy
- cleaned up the sensor code
- added test for comparison with original code output (TODO: move in another projecct)

It is based on the code/ideas from:
 - FreeIMU implementation: https://github.com/Fabio-Varesano-Association/freeimu
 - William Premerlani and Paul Bizard (paper) file:///home/mauro/Downloads/DCMDraft2.pdf
 - Madgwick implementation (paper): http://www.x-io.co.uk/res/doc/madgwick_internal_report.pdf
 - Mahony original paper https://hal.archives-ouvertes.fr/file/index/docid/488376/filename/2007_Mahony.etal_TAC-06-396_v3.pdf

[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/MauroMombelli/FreeDCM?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
