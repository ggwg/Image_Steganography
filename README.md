# <a name="introduction"></a>Image_Steganography
## Digital Image Steganography with Password Encryption

**An image steganography encoder which can hide files within the least significant bits of an image. The specified file can be optionally encrypted (using the AES encryption schema) with a password prior to being encoded within the target image.**

*This project was created as part of the Imperial College London's first year final group project, without the use of any existing libraries in C.*

Cryptography and steganography are both highly effective ways of protecting secret information - whilst steganography deals with hiding the existence of data, cryptography is able to hide the meaning of data. In the case that our encoding mechanism could be detected by some sort of AI program and somehow decoded, we agreed upon the need for a high level of encryption to prevent the original file from being deciphered. Therefore we decided that each byte of data to encode will be encrypted using a secure yet efficient encryption algorithm before encoding it into the image.

We discussed the advantages of some major encryption algorithms and considered whether each one would meet our design specifications. Ultimately we decided upon the Advanced Encryption Standard (AES) algorithm, which has benefits of sporting an excellent trade-off between efficiency, security and most importantly having 1-1 binary conversion (hence it does not increase the file size). There are 3 flavours of the AES algorithm: 128-bit, 192-bit and 256-bit. This describes how many bytes the AES algorithm encrypts in each round. For our program, and most commercial applications, AES-128 was the most suitable choice. One of the advantages of AES is that it uses a unique key each round, which makes deciphering the code extremely difficult. For example, for a file of size 5MB, it generates over 3 million unique keys during the encryption process (since there are 10 rounds for every 128 bytes of encryption).

Furthermore, to enhance the security of the encryption process, we implemented a password encryption process. This password can be optionally specified using the flag `-p <password>`, and this password is converted into the starting key for the encryption process using a hashing algorithm. Our program is able to encode files of literally any data type. An example is in `./test/out/shakespeare.bmp`. This image has the entire works of Shakespeare (in the form of a `.txt` file) encoded within itself using the password `romeo`. To prove this, run in terminal `./extension -d -i test/out/shakespeare.bmp -p romeo` and you will find a file `full_shakespeare.txt` has appeared.

**The program can be run using the following terminal commands (Note : password is optional):**

`Encoding: ./extension -e -i <*.bmp> <any file> -o <*.bmp> -p <password>`

`Decoding: ./extension -d -i <*.bmp> -p <password>`

## <a name="contents"></a>Table of Contents

<!--ts-->
   * [Introduction](#introduction)
   * [Table of Contents](#contents)
   * [What is Digital Image Steganography?](#whatis)
   * [Encoding Process](#encoding)
   * [Encryption Process](#encryption)
   * [Testing](#Testing)   
<!--te-->

## <a name="whatis"></a>What is Digital Image Steganography?

Steganography is closely linked to cryptography:

**Cryptography** - Someone may know a message has been sent, but can't find out what it means.

**Steganography** - Hiding the fact that a message even was sent at all.

As you can imagine, if you combine both these techniques together you have a pretty impressive and virtually uncrackable way of sending secret messages - and that's exactly what we've done!

## <a name="demo"></a>Demonstration

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

We run the executable again, this time specifying the correct password. Hurrah - it works, and we got Shakespeare's text file back!

![Extract original file (success)](/images/correct_password.JPG)

**6. Quality Comparison**

Here is a comparison of image quality between the original image and the image with Shakespeare's works encoded inside it:

![Comparison](/images/comparison.jpg)

# <a name="encoding"></a>Encoding Process

Encoding and decoding data from .BMP images is actually quite simple. Every pixel in a BMP image is represented by 3 bytes of code (red, green and blue), which ultimately determines the colour of that pixel. The algorithm we developed looks at both the size of the file to encode and the size of all the pixels in the image, and then determines the smallest bit encoding level possible to store the entire file within the image. The bit encoding level determines how many LSB bits of each pixel will be removed in order to store the data (the smaller the better). The encoding process works by using the first few bytes of the image to store meta data (necessary for decoding), and subsequently removing the last few bits of each pixel (at the bit encoding level). After this, the data to be encoded is iteratively stored in the LSB of each pixel.

The decode process works inversely; by first extracting the meta data which includes: the original file name, bit encoding level, and original file size. The last few bits of each pixel (at the extracted bit encoding level) are then pulled from the image, and rebuilt into the original file.

# <a name="encryption"></a>Encryption Process (AES-128 Cipher)

Before encryption and decryption can begin, the specified password must be converted into a key. To calculate the 16-byte starting key, we used 2 different hashing functions that convert the password string into 2 8-byte values and combined them together to form the unique 16-byte starting key, since gcc doesn’t support 128-bit integers on all architectures.

![Password Hashing Algorithm](/images/password.JPG)

Once we have calculated the key from the password, we can begin the AES encryption process. The Rijndael block cipher algorithms won the 2001 National Institute of Standards and Technology’s, and thus became dubbed the Advanced Encryption Standard. The image below gives a simple visual representation of the inner workings of the AES encryption algorithm.

![Password Hashing Algorithm](/images/aes.JPG)

As a very brief summary of AES encryption, 16 bytes of data, which can internally be thought of as a 4x4 matrix, are first XORed with the round key in a process called add_round_key(). Next, the result then goes through a sequence of sub_bytes(), shift_rows(), mix_columns() and add_round_key() processes a total of N times, with N being 10 for AES-128. The sub_bytes() operation represents a non-linear substitution step, whilst shift_rows() represents a transposition step whereby each row of the 4x4 matrix is shifted cyclically a different number of times. mix_columns() was particularly difficult to implement, and represents matrix multiplication by a predetermined matrix inside the Galois Field 2 8 - this provides diffusion in the columns. In the final round, the mix_columns() operation is not performed.

Crucially, the key changes continuously to ensure secure encryption, hence the name "round key" in AES. For every 16-bytes of data, the data goes through 10 rounds, and during each round the key changes to become a new computed value based on the previous round through a series of complex sub-byte look-ups, rcon operations and many XOR operations.

The decryption processes involves backtracking by undoing each step of the encryption process. Every operation used for encryption has its own inverse, and undoing XOR was especially easy since it is its own inverse. However, reversing the key schedule process proved to be especially challenging; not only was it required to calculate the key after 10 rounds, but inverting the round key process also proved to be highly challenging, since each version of the new key is calculated using the previous key.

As a result of our rigorous password hashing and complex encryption process, if a user enters even a single character of the password process incorrectly then the resulting file output will be completely unreadable. Furthermore, large files of several Megabytes can be encrypted and encoded (or decoded and decrypted) within seconds, due to the highly efficient algorithms we implemented.

# <a name="testing"></a>Testing

Various tests were performed to ensure optimal performance and reliablilty.

- **Memory Checks** - We regularly used Valgrind to identify any memory leaks and ensure all allocated memory was being freed before program termination. There are no memory leaks in our extension.

- **Encoding & Decoding** - As encoding and decoding are the inverse of each other, we were able to test how well our extension was doing by first encoding a file, and checking if decoding the result gave us back the original file. We encoded and decoded a large range of file types, including .txt, .pdf, .zip and even .wav files and concluded that in every case decoding the image resulted in a perfect replica of the original file.
