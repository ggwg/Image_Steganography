# Image_Steganography
### *Digital Image Steganography with Password Encryption*

An image steganography encoder which can hide files within the least significant bits of an image. The specified file can be optionally encrypted (using the AES encryption schema) with a password prior to being encoded within the target image.

This project was created without the use of any existing libraries in C, as part of the Imperial College London's first year final group project.

## Table of Contents

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

## Demonstration

**1. The Original Image**

We are going to be encoding the whole of Shakespeare's works (120,000 lines!) inside of the image below. The text document containing all of Shakespeare's works is 5.5 MB in size, whereas the image is only 11 MB in size.

![Original Image (before encoding)](/images/original_image.JPG)

**2. Calling the program from the terminal**

Next, we run the program executable, specifying an input image and an input file. We've also entered a password "Gavin1234", which will tell the program to encrypt the binary file data before encoding it within the image.

![Run the executable from the command line](/images/1.JPG)

**3. Viewing the encoded image, with Shakespeare's works hidden inside!**

Below is the output after Shakespeare's works have been encoded inside the original image. As you can see, despite the input file being half the size of the image itself, the quality is still surprisingly good!

![Encoded Image](/images/encoded_image.JPG)

**4. Decoding the Image (Wrong Password)**

When we decode the image with an incorrect passcode, we don't get the original Shakespeare text document back - that's because the decryption failed.

![Extract original file (failed)](/images/incorrect_password.JPG)

**5. Decoding the Image (Correct Password)**

When we decode the image with an incorrect passcode, we don't get the original Shakespeare text document back - that's because the decryption failed.

![Extract original file (success)](/images/correct_password.JPG)
![Comparison](/images/comparison.jpg)


