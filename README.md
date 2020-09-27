# Image_Steganography - Digital Image Steganography with Password Encryption

An image steganography encoder which can hide files within the least significant bits of an image. The specified file can be optionally encrypted (using the AES encryption schema) with a password prior to being encoded within the target image.

This project was created without the use of any existing libraries in C, as part of the Imperial College London's first year final group project.

Table of contents
=================

<!--ts-->
   * [gh-md-toc](#gh-md-toc)
   * [Table of contents](#table-of-contents)
   * [Installation](#installation)
   * [Usage](#usage)
      * [STDIN](#stdin)
      * [Local files](#local-files)
      * [Remote files](#remote-files)
      * [Multiple files](#multiple-files)
      * [Combo](#combo)
      * [Auto insert and update TOC](#auto-insert-and-update-toc)
      * [GitHub token](#github-token)
   * [Tests](#tests)
   * [Dependency](#dependency)
<!--te-->

## What is Digital Image Steganography?

Steganography is closely linked to cryptography:

**Cryptography** - Someone may know a message has been sent, but can't find out what it means.
**Steganography** - Hiding the fact that a message even was sent at all.

As you can imagine, if you combine both these techniques together you have a pretty impressive and virtually uncrackable way of sending secret messages - and that's exactly what we've done!
