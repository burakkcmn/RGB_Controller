# ESP8266 RGB LED Controller

This project is an RGB LED controller using an ESP8266 with PlatformIO. It provides WiFi and web-based control over the LEDs, including various animations.

## Features

- Control 3 separate RGB LED channels.
- Set individual colors and brightness for each channel.
- Choose from multiple predefined animations.
- Web interface for controlling the LEDs and setting animations.
- WiFi configuration via a web portal in AP mode.

## Hardware Requirements

- ESP8266 (e.g., NodeMCU)
- Common anode RGB LED strip
- Resistors (optional, to limit current)
- Breadboard and jumper wires

## Software Requirements

- PlatformIO
- Arduino framework
- Required libraries (specified in `platformio.ini`)

## Wiring

| LED Channel | Red Pin | Green Pin | Blue Pin |
|-------------|---------|-----------|----------|
| Channel 1   | D1      | D2        | D3       |
| Channel 2   | D4      | D5        | D6       |
| Channel 3   | D7      | D8        | D9       |

## Installation

1. Clone this repository.
    ```sh
    git clone https://github.com/burakkcmn/RGB_Controller.git
    ```
3. Open the project folder in PlatformIO.
4. Build and upload the project to your ESP8266 board.

## Usage

1. Power up your ESP8266. It will attempt to connect to a saved WiFi network. If it fails, it will start an access point.
2. Connect to the access point named `ESP8266_AP` with the password `12345678`.
3. Open a web browser and navigate to `http://192.168.4.1`.
4. Enter your WiFi credentials to connect the ESP8266 to your network.
5. Once connected, use the web interface to control the RGB LEDs.

## API Endpoints

- `/`: Main page.
- `/control`: Control page for setting colors and animations.
- `/set_color`: Set color of a specific channel.
  - Parameters: `channel`, `color` (hex), `brightness`
- `/set_animation`: Set the current animation.
  - Parameters: `animation`

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- [ESPAsyncWiFiManager](https://github.com/alanswx/ESPAsyncWiFiManager)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [DNSServer](https://github.com/bbx10/DNSServer)

## Contact

For any inquiries or feedback, please contact [Burak KOCAMAN](kocaman.burak.bk@gmail.com).

This README provides a comprehensive overview of your project, including setup instructions, usage details, and code structure. Adjust the content as needed to better fit your specific project requirements.

## Author
- **Burak KOCAMAN**
  - GitHub: [burakkcmn](https://github.com/burakkcmn)
  - Email: [kocaman.burak.bk@gmail.com](mailto:kocaman.burak.bk@gmail.com)
