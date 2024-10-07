# Wokwi-Chip-TB6612FNG
## Description

TB6612FNG Dual H-bridge motor driver

-  

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
"dependencies": { "chip-tb6612fng": "github:drf5n/Wokwi-Chip-TB6612FNG@1.0.0" }
```

Then, add the chip to your circuit by adding a `chip-tb6612fng` item to the `parts` section of `diagram.json`:

```json
  "parts": {
    ...,
    {
      "type": "chip-tb6612fng",
      "id": "driver1",
      "attrs": { }
    },
```

The actual source code for the chip lives in [src/main.c](https://github.com/drf5n/Wokwi-Chip-TB6612FNG/blob/main/src/main.c), and the pins are described in [chip.json](https://github.com/drf5n/Wokwi-Chip-TB6612FNG/blob/main/chip.json).

## Examples

* [Wokwi Mega with TB6612FNG](https://wokwi.com/projects/411109185758524417) -- with stepper-esc+stepper for DC motor simA
* [Wokwi Uno with TB6612FNG]](https://wokwi.com/projects/411112944848391169) -- with LED-motors and scopes
* [Wokwi Uno with TB6612FNG driver  using tabbed files](https://wokwi.com/projects/410323062531374081) -- with LED-motors and scopes

## See also:

* https://github.com/drf5n/Wokwi-Chip-stepper-esc -- for a stepper-ESC custom chip to control a stepper with PWM like a DC motor.
* https://github.com/drf5n/Wokwi-Chip-L298N for a less efficient dual-h-bridge motor driver custom chip.

## Versions
* github:drf5n/Wokwi-Chip-TB6612FNG@1.0.0 -- Working release


# notes on making a Wokwi custom chip work with Github repository dependency
To get the Wokwi build script working to build the necessary chip.zip file for distribution with a release so Wokwi can pick it up

1) enable the repository settinggs for wokflow permissions to be read-write
2) make sure the .github/workflows/build.yaml is in the repository
3) commit
4) make a vN.n.n tag: `git tag -a "v1.0.5" -m "build.yaml"`
5) push the tag  to github: `git push origin tag v1.0.5`

Refer to https://discord.com/channels/787627282663211009/954892209486966825/1274569798231130163 for a little discussion 


## License

This project is licensed under the MIT license. See the [LICENSE](https://github.com/drf5na/Wokwi-Chip-L298N/blob/main/LICENSE) file for more details.
