PAMA TECHNOLOGIES COMPUTER VISION PROGRAMMING TEST
----------------------------------------------------

APPLICATION DESCRIPTION
-----------------------
    This application detects edges (for every color channel) in RGB images.


YOUR TASKS
----------

    1.) in the main function you have to choose the correct filter for the following steps :
        a) lowpass filter
        b) horizontal edge detection
        c) vertical edge detection

        The file Kernel.h provides several predefined filter types, please choose the correct one/ones and initialize
        the Filter-Object method : filter.init(????);


    2.) implement the convolution algorithm defined in the Filter class.

            void convolve (PPMImage & srcImage, PPMImage & destImage);


    3.) the main.cpp contains the following prototypes:

            PPMImage& calcMagnitudeForEveryChannel(PPMImage&, const PPMImage&, const PPMImage&);
            PPMImage& filterImage(Filter3x3<3>&, PPMImage&);

        Implement these two functions, so that the main program runs correctly.


        HINTS : please write your code (comments, variables, functions etc.) in english!


TIME
-----

    For these tasks you have a maximum time of 4 hours.
    If you are finished send us the complete project back as a zip-file (no rar, tar or other formats, ONLY ZIP).

    email : sven.luenser@pama-tech.com



