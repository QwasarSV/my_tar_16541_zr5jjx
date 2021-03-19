This repository contains my emulation of the "tar" command for archiving and extracting files.

**Architecture and data structures:**

For this project, I took a rather unconventional approach which allowed me to explore the C language in a way that I
hadn't before. Before this project I had certainly used structs extensively and I had used pointers to functions, though
addmittely not as much. What I did in this project that I had never done before was combine the two by creating structs
that housed pointers to functions which simulates the way in which classes work in higher level languages. At first it felt
like an interesting proof of concept, but as I worked with it more and more, I felt like I was able to really create much
cleaner code than I would have been able to otherwise. Being able to group like functions in structs makes the code very
easy to follow and modify for someone who may or may not have seen it before.

In addition to discovering what felt like a new way to "C" (pun intended), I learned all the ins, out, and functionality of
the 'tar' command. I have performed quite a bit of extensive research on the command understanding its strengths and
limitations, and I understand the format of the archive so well I could accurately write it on paper if fed file
information.

Overall this project has been an incredible learning experience on multiple levels and I am certainly a more proficient
programmer as a result!

**Functionality and how to run:**

To create and executable, run 'make' in the terminal to create an executable called 'my_tar'.
You can operate my_tar in 5 different modes:
   * -c = create archive
   * -t = list archive
   * -x = extract archive
   * -r = append file(s) to existing archive
   * -u = like -r but only append if the modification time of the file is newer than its counterpart in the archive
Each of these options must also be accompanied by the -f flag to signify the name of the archive that you will be working with.

syntax for running the program is as follows:
    ./my_tar [-OPERATING MODE][-f] [ARCHIVE FILENAME] [FILE1] [FILE2] [...]
Note: including additional filenames at the end may not be necessary for all operating modes

Be careful when running the command that you specify the archive name as the first file.
If an existing file is specified beforehand it will be assumed to be the archive and will be overwritten.