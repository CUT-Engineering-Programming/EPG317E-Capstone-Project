# EPG317E — Engineering Programming III  
# Capstone Project: IoT Smart Farm Monitoring & Control Dashboard

**Central University of Technology, Free State**  
**Department of Electrical, Electronic and Computer Engineering**  


---

## 1. Project Overview

Your team will design, build, and deploy a **real-time IoT monitoring and control dashboard** for the **Keyestudio ESP32 IoT Smart Farm Kit (KS0567)**. The ESP32 will collect sensor data from the kit's agricultural sensors, publish it via **MQTT** to a cloud broker, and receive control instructions from a **Panel (Python)** web dashboard. All sensor data will be stored in a **SQLite** database and the dashboard will be deployed on **PythonAnywhere**.

This project integrates embedded systems programming (C/C++ on ESP32), IoT communication protocols (MQTT), data storage (SQLite), data visualisation (Panel/HoloViz), and web deployment — skills that are directly applicable to modern engineering practice, particularly in precision agriculture and smart farming systems.

### 1.1 Learning Outcomes

Upon completion of this project, students will be able to:

- Program an ESP32 microcontroller to read sensors and communicate over Wi-Fi using MQTT.
- Design and implement an MQTT topic structure for a multi-sensor IoT system.
- Build a real-time web dashboard using Python Panel that displays live and historical data.
- Store time-series sensor data in a SQLite database and query it for visualisation.
- Deploy a Python web application on PythonAnywhere.
- Collaborate effectively using Git, GitHub, feature branches, and pull requests.
- Document and present a technical engineering project professionally.

---

## 2. Your Kit — Keyestudio ESP32 IoT Smart Farm Kit (KS0567)

<img src="https://m.media-amazon.com/images/I/71+xBUgi8dL._AC_UF1000,1000_QL80_.jpg" alt="Keyestudio ESP32 IoT Smart Farm Kit (KS0567)" width="400"/>

**Kit Documentation:** [https://wiki.keyestudio.com/KS0567_Keyestudio_ESP32_IoT_Control_Smart_Farm_Starter_Kit_for_Arduino_Scratch_3.0_Graphical_Programming](https://wiki.keyestudio.com/KS0567_Keyestudio_ESP32_IoT_Control_Smart_Farm_Starter_Kit_for_Arduino_Scratch_3.0_Graphical_Programming)

### 2.1 Key Components

| Component | Purpose | Interface |
|-----------|---------|-----------|
| ESP32 PLUS Development Board | Main controller with Wi-Fi/Bluetooth | — |
| Soil Humidity Sensor | Measure soil moisture levels | Analog |
| DHT11 Temperature & Humidity Sensor | Monitor ambient climate conditions | Digital |
| Water Level Sensor | Detect water level in reservoir/tank | Analog |
| Photoresistor | Measure ambient light intensity | Analog |
| PIR Motion Sensor | Detect motion (animal intrusion detection) | Digital |
| Ultrasonic Sensor (SR01 V3) | Distance measurement (tank level / object detection) | Digital (Trig/Echo) |
| Steam / Rain Sensor | Detect rainfall or condensation | Analog |
| DC 3V Water Pump | Automated irrigation | Digital (via relay) |
| 5V Relay Module | Switch high-current devices (pump, fan) | Digital |
| 130 Motor + Fan | Ventilation control | Digital (PWM) |
| 9G Servo Motor (180°) | Gate/valve control | PWM |
| Passive Buzzer | Audio alerts (intrusion, low water) | Digital |
| White LED Module | Grow light / status indicator | Digital |
| Button Module | Manual user input | Digital |
| I2C 1602 LCD Display | Local status display | I2C |
| Solar Panel | Energy awareness / supplementary power | PH2.0 connector |

### 2.2 Suggested Sensor Data to Collect

Your ESP32 firmware should read and publish (at minimum) the following data over MQTT:

- **Soil moisture** level (analog value → percentage)
- **Temperature** (°C) from DHT11
- **Humidity** (%) from DHT11
- **Water level** in tank/reservoir (analog value)
- **Ambient light** level from photoresistor (analog value / lux estimate)
- **Rainfall detection** from steam/rain sensor (analog value)
- **Motion detection** from PIR sensor (binary: detected / not detected)
- **Ultrasonic distance** reading (cm) for tank water level
- **Pump status** (on/off)
- **Fan status** (on/off)

### 2.3 Suggested Control Actions (Dashboard → ESP32)

Your dashboard should be able to send the following commands to the ESP32 via MQTT:

- **Toggle water pump** on/off (manual irrigation)
- **Toggle fan/ventilation** on/off
- **Control servo** — open/close gate or valve (set angle)
- **Toggle LED** (grow light) on/off
- **Set soil moisture threshold** — below which auto-irrigation activates
- **Set temperature threshold** — above which auto-ventilation activates
- **Arm/disarm motion alert** — enable/disable PIR-based intrusion alerts

---

## 3. Technical Requirements

### 3.1 ESP32 Firmware (Arduino IDE / C++)

- Program the ESP32 using the **Arduino IDE**.
- Connect to Wi-Fi and an **MQTT broker** of your team's choice (any free broker is acceptable, e.g., HiveMQ Cloud, Mosquitto test broker, EMQX Cloud, etc.).
- Publish sensor data to structured MQTT topics at a regular interval (e.g., every 5–10 seconds).
- Subscribe to control topics and execute commands received from the dashboard.
- Design a clear **MQTT topic structure**, for example:
  ```
  epg317e/farm/<team_id>/sensors/soil_moisture
  epg317e/farm/<team_id>/sensors/temperature
  epg317e/farm/<team_id>/sensors/humidity
  epg317e/farm/<team_id>/sensors/water_level
  epg317e/farm/<team_id>/sensors/light
  epg317e/farm/<team_id>/sensors/rain
  epg317e/farm/<team_id>/sensors/motion
  epg317e/farm/<team_id>/sensors/ultrasonic
  epg317e/farm/<team_id>/actuators/pump_status
  epg317e/farm/<team_id>/actuators/fan_status
  epg317e/farm/<team_id>/control/pump
  epg317e/farm/<team_id>/control/fan
  epg317e/farm/<team_id>/control/servo
  epg317e/farm/<team_id>/control/led
  epg317e/farm/<team_id>/control/threshold_soil
  epg317e/farm/<team_id>/control/threshold_temp
  ```

**Download Arduino IDE:** [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

**ESP32 Board Setup for Arduino IDE:** Follow the official Espressif guide to add the ESP32 board package:  
[https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

### 3.2 MQTT Broker

- Use **any free MQTT broker** of your choice.
- Popular options include:
  - [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) (free tier)
  - [EMQX Cloud](https://www.emqx.com/en/cloud) (free tier)
  - [Mosquitto Test Broker](https://test.mosquitto.org/)
- Document your broker choice, connection details, and topic structure in your portfolio.

### 3.3 Python Dashboard (Panel / HoloViz)

Build a web-based dashboard using **Panel** ([https://panel.holoviz.org/](https://panel.holoviz.org/)) that provides:

**Live Data Display:**
- Real-time readings of all sensors (soil moisture, temperature, humidity, water level, light, rain).
- Motion alert indicator (with timestamp of last detection).
- Pump and fan status indicators (on/off).
- Ultrasonic-based water tank level visualisation.
- Timestamps for the most recent data received.

**Historical Data Display:**
- Time-series plots (line charts) of soil moisture, temperature, humidity, water level, and light over selectable time ranges (last 1 hour, 6 hours, 24 hours, 7 days).
- Motion event log (table showing timestamps of motion detections).
- Use **Matplotlib**, **hvPlot**, or **Bokeh** (all compatible with Panel) for plotting.

**Control Panel:**
- Buttons/toggles to send MQTT commands to the ESP32 (pump, fan, LED, servo, motion alert).
- Sliders or input fields for setting thresholds (soil moisture, temperature).

**Dashboard Quality:**
- Clean, professional layout with clear labels, units, and colour coding.
- Responsive to data updates.
- Error handling for lost MQTT connections.

### 3.4 Database (SQLite)

- Use **SQLite** to store all incoming sensor data with timestamps.
- Design an appropriate database schema (e.g., a table per sensor type or a single table with a sensor type column).
- The dashboard must query the database for historical data display.
- Include a script or mechanism to initialise the database schema.

### 3.5 Deployment (PythonAnywhere)

- Deploy your Panel dashboard on **PythonAnywhere** using a **free-tier account** (register at [https://www.pythonanywhere.com/](https://www.pythonanywhere.com/)).
- The dashboard must be accessible via a public URL for demonstration and assessment.
- Document the deployment steps in your portfolio.

---

## 4. GitHub & Version Control Requirements

### 4.1 Repository Setup

- Create a **single GitHub repository** per team.
- The repository must be set to **public** (or grant the instructor access if private).
- Include a well-written `README.md` with:
  - Project title and description
  - Team members and student numbers
  - Setup and installation instructions
  - MQTT topic structure documentation
  - Link to deployed dashboard
  - Wiring diagram or photo of the assembled kit

### 4.2 Branching Strategy — Feature Branches + Pull Requests

Your team must follow a **feature branch** workflow:

1. The `main` branch always contains working, tested code.
2. Each team member creates a **feature branch** from `main` for each task they work on. Branch names should be descriptive, e.g.:
   - `feature/mqtt-connection`
   - `feature/soil-moisture-reading`
   - `feature/dashboard-layout`
   - `feature/database-schema`
   - `feature/pump-control`
   - `fix/humidity-calibration`
3. When a feature is complete, the team member opens a **Pull Request (PR)** to merge into `main`.
4. At least **one other team member** must review and approve the PR before merging.
5. **Individual contributions will be assessed based on pull requests.** Each member must have meaningful PRs that demonstrate their contribution to the codebase.

### 4.3 Minimum Contribution Expectations

- Every team member must have **at least 3 meaningful pull requests** merged into `main`.
- PRs must contain real, substantive work — not trivial changes like fixing typos or reformatting.
- Commit messages must be clear and descriptive.
- The PR description should explain what was changed and why.

---

## 5. Assessment

Refer to the [README.md](README.md) for the full assessment rubrics (Code, Presentation & Demo).

---

## 6. Resources & Links

### Software Downloads
- **Arduino IDE:** [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
- **ESP32 Arduino Core Installation:** [https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
- **Python (3.10+):** [https://www.python.org/downloads/](https://www.python.org/downloads/)
- **Git:** [https://git-scm.com/downloads](https://git-scm.com/downloads)



### Documentation
- **Panel (HoloViz):** [https://panel.holoviz.org/](https://panel.holoviz.org/)
- **Paho MQTT (Python):** [https://pypi.org/project/paho-mqtt/](https://pypi.org/project/paho-mqtt/)
- **PubSubClient (ESP32 Arduino MQTT):** [https://github.com/knolleary/pubsubclient](https://github.com/knolleary/pubsubclient)
- **SQLite with Python:** [https://docs.python.org/3/library/sqlite3.html](https://docs.python.org/3/library/sqlite3.html)
- **PythonAnywhere:** [https://www.pythonanywhere.com/](https://www.pythonanywhere.com/)
- **GitHub Docs — Pull Requests:** [https://docs.github.com/en/pull-requests](https://docs.github.com/en/pull-requests)

### Kit Resources
- **KS0567 Smart Farm Kit Documentation:** [https://wiki.keyestudio.com/KS0567_Keyestudio_ESP32_IoT_Control_Smart_Farm_Starter_Kit_for_Arduino_Scratch_3.0_Graphical_Programming](https://wiki.keyestudio.com/KS0567_Keyestudio_ESP32_IoT_Control_Smart_Farm_Starter_Kit_for_Arduino_Scratch_3.0_Graphical_Programming)
- **Kit Code & Libraries Download:** [https://fs.keyestudio.com/KS0567](https://fs.keyestudio.com/KS0567)
- **ESP32 PLUS Board Documentation:** [https://wiki.keyestudio.com/KS5016_Keyestudio_ESP32_PLUS_Development_Board](https://wiki.keyestudio.com/KS5016_Keyestudio_ESP32_PLUS_Development_Board)

### MQTT Brokers (Free Tier)
- **HiveMQ Cloud:** [https://www.hivemq.com/mqtt-cloud-broker/](https://www.hivemq.com/mqtt-cloud-broker/)
- **EMQX Cloud:** [https://www.emqx.com/en/cloud](https://www.emqx.com/en/cloud)
- **Mosquitto Test Broker:** [https://test.mosquitto.org/](https://test.mosquitto.org/)

---

## 7. Important Notes

- **Team Size:** 5–6 students per team (existing groups).
- **Submission:** All deliverables (code, portfolio, presentation slides) must be submitted via the LMS. Check the LMS for submission dates and detailed instructions.
- **Academic Integrity:** All work must be original. Code copied from external sources must be attributed. Plagiarism in the portfolio will result in disciplinary action.
- **Late Submissions:** Refer to the LMS for the late submission policy.
- **Hardware Care:** Handle the kit components with care. You are responsible for the condition of the kit. Keep water away from electronic components (except the waterproof parts of designated sensors). Do not over-water when testing the pump.

---

*EPG317E — Engineering Programming III | Central University of Technology, Free State*
