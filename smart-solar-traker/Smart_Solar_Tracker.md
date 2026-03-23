# EPG317E — Engineering Programming III  
# Capstone Project: IoT Solar Tracker Monitoring & Control Dashboard

**Central University of Technology, Free State**  
**Department of Electrical, Electronic and Computer Engineering**  


---

## 1. Project Overview

Your team will design, build, and deploy a **real-time IoT monitoring and control dashboard** for the **Keyestudio Solar Tracking Kit (KS0530)**, modified to use an **ESP32** microcontroller. The ESP32 will collect sensor data from the kit's hardware, publish it via **MQTT** to a cloud broker, and receive control instructions from a **Panel (Python)** web dashboard. All sensor data will be stored in a **SQLite** database and the dashboard will be deployed on **PythonAnywhere**.

This project integrates embedded systems programming (C/C++ on ESP32), IoT communication protocols (MQTT), data storage (SQLite), data visualisation (Panel/HoloViz), and web deployment — skills that are directly applicable to modern engineering practice.

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

## 2. Your Kit — Keyestudio Solar Tracking Kit (KS0530)

<img src="https://ueeshop.ly200-cdn.com/u_file/UPAH/UPAH808/2110/photo/3bec3f8035.jpg" alt="Keyestudio Solar Tracking Kit (KS0530)" width="400"/>

**Kit Documentation:** [https://docs.keyestudio.com/projects/KS0530/en/latest/KS0530.html](https://docs.keyestudio.com/projects/KS0530/en/latest/KS0530.html)

> **Note:** The original Arduino UNO board included in this kit has been replaced with an **ESP32** development board to enable Wi-Fi and MQTT connectivity.

### 2.1 Key Components

| Component | Purpose | Interface |
|-----------|---------|-----------|
| ESP32 Development Board | Main controller with Wi-Fi/Bluetooth | — |
| 4 × Photoresistor / Light Sensors | Detect ambient light for solar tracking | Analog |
| 2 × Servo Motors (Pan & Tilt) | Adjust solar panel angle | PWM |
| Solar Panel | Energy harvesting | PH2.0 connector |
| Solar USB Charging Module | Battery charge management | PH2.0 connector |
| 18650 Battery Case | Energy storage | PH2.0 connector |
| DHT11 Sensor | Temperature & humidity | Digital |
| BH1750 Light Sensor | Precise lux measurement | I2C |
| Passive Buzzer | Audio alerts | Digital |
| LCD 1602 (I2C) | Local display | I2C |
| Push Button Module | User input | Digital |
| LED Module | Status indicator | Digital |
| Phone Charging Module | 3.7V boost to 5V USB output | PH2.0 / USB |

### 2.2 Suggested Sensor Data to Collect

Your ESP32 firmware should read and publish (at minimum) the following data over MQTT:

- **Light intensity** from BH1750 (lux) and/or photoresistors (analog values)
- **Temperature** (°C) from DHT11
- **Humidity** (%) from DHT11
- **Solar panel orientation** — current servo angles (pan and tilt)
- **Battery voltage** (via the charging module's S pin, after voltage divider)
- **Tracking mode status** — whether auto-tracking is active or manual

### 2.3 Suggested Control Actions (Dashboard → ESP32)

Your dashboard should be able to send the following commands to the ESP32 via MQTT:

- **Toggle auto-tracking** on/off
- **Manual servo control** — set pan and tilt angles
- **Toggle LED** on/off
- **Trigger buzzer alert**
- **Set light threshold** for auto-tracking sensitivity

---

## 3. Technical Requirements

### 3.1 ESP32 Firmware (Arduino IDE / C++)

- Program the ESP32 using the **Arduino IDE**.
- Connect to Wi-Fi and an **MQTT broker** of your team's choice (any free broker is acceptable, e.g., HiveMQ Cloud, Mosquitto test broker, EMQX Cloud, etc.).
- Publish sensor data to structured MQTT topics at a regular interval (e.g., every 5–10 seconds).
- Subscribe to control topics and execute commands received from the dashboard.
- Design a clear **MQTT topic structure**, for example:
  ```
  epg317e/solar/<team_id>/sensors/temperature
  epg317e/solar/<team_id>/sensors/humidity
  epg317e/solar/<team_id>/sensors/lux
  epg317e/solar/<team_id>/sensors/battery
  epg317e/solar/<team_id>/actuators/servo_pan
  epg317e/solar/<team_id>/actuators/servo_tilt
  epg317e/solar/<team_id>/control/tracking_mode
  epg317e/solar/<team_id>/control/led
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
- Real-time readings of all sensors (temperature, humidity, light, battery voltage).
- Current solar panel orientation (servo angles) with a visual representation.
- Auto-tracking mode status indicator.
- Timestamps for the most recent data received.

**Historical Data Display:**
- Time-series plots (line charts) of temperature, humidity, light intensity, and battery voltage over selectable time ranges (last 1 hour, 6 hours, 24 hours, 7 days).
- Use **Matplotlib**, **hvPlot**, or **Bokeh** (all compatible with Panel) for plotting.

**Control Panel:**
- Buttons/toggles to send MQTT commands to the ESP32 (toggle tracking, manual servo control, LED, buzzer).
- Input fields or sliders for setting servo angles and thresholds.

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
   - `feature/dashboard-layout`
   - `feature/database-schema`
   - `feature/servo-control`
   - `fix/temperature-reading-bug`
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
- **KS0530 Solar Tracking Kit Documentation:** [https://docs.keyestudio.com/projects/KS0530/en/latest/KS0530.html](https://docs.keyestudio.com/projects/KS0530/en/latest/KS0530.html)
- **Kit Code & Libraries Download:** [https://fs.keyestudio.com/KS0530](https://fs.keyestudio.com/KS0530)

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
- **Hardware Care:** Handle the kit components with care. You are responsible for the condition of the kit. Do not expose batteries or solar panels to excessive heat.

---

*EPG317E — Engineering Programming III | Central University of Technology, Free State*
