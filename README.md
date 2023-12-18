**Notice:** This repo was a clone of the one on [Dominic Radermacher's website](https://mockmoon-cybernetics.ch/computer/p-touch2430pc/), and he is the original author. The original is available at (https://github.com/clarkewd/ptouch-print/), with his permission, to help increase visibility of the project and to encourage collaboration and further development.


# ptouch-print

ptouch-print is a command line tool to print labels on Brother P-Touch
printers on macOS.

There is no need to install the printer via CUPS, the printer is accessed
directly via libusb.

The tool was written for and tested with the `PT-2730`, but it should also
work with the `PT-2430PC` and `PT-1230PC` (untested so far). Maybe others work too (please report USB VID and PID so I can include support for further models, too).

**Models in `libptouch.c` include:**

- PT-2420PC
- PT-1230PC
- PT-2430PC
- PT-2730
- PT-P700 ( see note below about mode switch )
- PT-D450

**Further info can be found at:**
https://mockmoon-cybernetics.ch/computer/p-touch2430pc/

### Compile instructions:

  The project is self-contained. There are no additional dependencies.

  Open the Xcode project. Use the menu command **Product** > **Run**

### PT-2730 on Mac:

Brother dropped support for the PT-2730 with the release of macOS Big Sur (version 11.0) in 2020.

I am furious that Brother dropped support. How hard can it be, it's just a simple USB device?

So I brought this Linux command line tool to macOS. (I checked that it wasn't already in macPorts.)

The commandline tool depended on two other libraries: 

* libUSB - so I grabbed the relevant source files, and include them here.

* libgd - a graphics manipulation library. I just re-implemented what I needed from it in terms of 
the Core Graphics framework that ships with macOS.

For fonts, You can use any of the font names in **/Applications/Font Book**. For fonts with variants
in Font Book like **Bold** or **Italic** just append those modifiers. **Helvetica** is the default font.

## example command lines:

`~$ ptouch-print --font "Snell Roundhand Black" --text "Hello World  " --writepng "ptouch.png"`


<span style="color:gray">PT-2730 found on USB bus 4, device 17</span>

<span style="color:gray">choosing font size=95</span>


`~$ ptouch-print --font "Snell Roundhand" --text "Hello World  " --writepng "ptouch1.png"`

<span style="color:gray">PT-2730 found on USB bus 4, device 17</span>

<span style="color:gray">choosing font size=95</span>


### PT-2730

My **PT-2730** always wants to put 1" of leader on each print. If the print is just simple
text, the **PT-2730** doesn't print the first half of the first character. But if I include a small
.png first, then the whole png and the following text print just fine. I generally test by having
`ptouch-print` write to a png first, as a preview of what will print.

Here is the actual command line I used to print labels for the jars in my refrigerator:

`ptouch-print --image /Users/david/spiral.png --cutmark --text \ Sauerkraut\  --cutmark --text \ Yeast\  --cutmark --text \ Yeast\  --cutmark --text \ Yeast\  `

where `spiral.png` is: ![](images/spiral.png)

multiple lines of text would be:

`ptouch-print --text "line 1" "line 2" "line 3"`

### PT-P700:

- As the PT-P700 does not have a toggle switch for the printer mode, you may need to switch the mode first
- If you plug in the PT-P700 and the green light above the PLite button is on, the printer won't be recognized by `ptouch`. You must hold down the PLite button for ~ 2 seconds and the light will turn off and the system will find the device again.
- This step allowed it to be detected as `vid 0x04F9 pid 0x2061` insetad of `vid 0x04F9 pid 0x2064`
- This allows it to be found, (eg: `./ptouch-print --info`) and also puts it into a mode that it can be interfaced with


### A Note from Dominic's website

"Dear visitor, currently I have absolutely no time for improvements on this project (my free time currently is about one or two hours PER MONTH)..."

### Collaboration

You may still, of course, contact Dominic directly if you'd like. But I think GitHub is easier for collaboration, and he has given me permission to host a clone of his repo here, passing code contributions back to him.

### License

The original ptouch-print is GNU GPL 3, so my work is too. libusb is under the MIT license.

