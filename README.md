# Arduino Techno Music Visualizer using NeoPixels and the Spectrum Shield spectrum analyzer 

I'm a volunteer at the [Idea Fab Labs](https://santacruz.ideafablabs.com/) maker/hacker/artspace here in Santa Cruz, and I was asked to take an Arduino Uno, [Spectrum Shield](https://www.sparkfun.com/products/13116) audio spectrum analyzer Arduino shield, and a strip of [NeoPixels](https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels), and write an Arduino sketch that, when you played a techno song like [Aaliyah - Rock The Boat (AtYyA Remix)](https://www.youtube.com/watch?v=lO6Vz_cvsGo), on each drumbeat the NeoPixels would go to full brightness and then fade. I'll probably add more features to this visualizer later, but right now it's just a short simple sketch that does what it was supposed to do.

To run it, you'll need to install the [FastLED](http://fastled.io/) Arduino NeoPixels library, and in the sketch set these constants to match your setup:
* `NUM_LEDS` - The number of NeoPixels or NeoPixel-like LEDs in your NeoPixel strip or shield.
* `LED_TYPE` - The type of NeoPixels in your strip or shield.
* `COLOR_ORDER` - The color order used by your LEDs.

See the [FastLED library site](http://fastled.io/) for more info on using different types of NeoPixels and NeoPixel-like LEDs, including what values to use for the `LED_TYPE` and `COLOR_ORDER` constants.

Note that the audio input on the Spectrum Shield is not very sensitive -- when you're running music or other audio into it you need to have the volume set much higher than you would need to for headphones. 

There are three more constants you can set to "tune" the visualizer:
* `DRUM_VOLUME_THRESHOLD` - The Spectrum Shield splits stereo audio input into seven bands for each of the two channels, so you're looking at the volume of a frequency band rather than being able to isolate a particular frequency. In experimenting with the seven bands I found that band 4 worked best with the techno music we were using, to respond to all the drumbeats but ignore the other elements of the music. In the sketch I set `DRUM_VOLUME_THRESHOLD` to 170 (out of 255), but it's really going to depend on the volume of the music you've got going into the audio input -- too low a volume and some or all of the drumbeats won't be loud enough for that threshold, or with the volume too high, some other musical elements that include frequencies within that band may trigger it as well. 
* `BRIGHTNESS` - Leave `BRIGHTNESS` set to 255 for the LEDs to start out set to full brightness before fading, or if that's too blinding for you you can set it to a lower number.
* `FADE_DELAY` - Leave `FADE_DELAY` set to 1 for a good basic fade when `BRIGHTNESS` is set to 255, or decrease it to 0 for a quicker fade, or increase it to 2, 3, etc. for a more drawn-out fade. For lower `BRIGHTNESS` settings, you will want to increase `FADE_DELAY` so that the smaller amount of difference between on and off gets stretched out more rather than just looking like the LEDs were turned right off again. Also, if your Arduino or Arduino-compatible board runs faster or slower than the Arduino Uno, the fading may be shorter or longer as well, so that would be another reason to tweak this to whatever timing you prefer.

Have fun!
