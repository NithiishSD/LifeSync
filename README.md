# LifeSync

A C++ and Qt-based organ donation management application designed to manage donor information, recipient workflows, and donor matching through a desktop graphical interface.

---

## Overview

Finding suitable organ donors requires managing donor information, recipient requirements, medical information, and compatibility factors efficiently.

LifeSync provides a desktop-based interface for managing donor and recipient information and presenting suitable donor matches based on available matching information.

---

## Features

- Donor registration
- Recipient registration and management
- Donor information management
- Recipient workflow management
- Donor matching
- Compatibility-based matching information
- Distance-based donor information
- Donor medical information
- Hospital information
- Interactive Qt desktop interface
- Informational content about organ donation

---

## Application Workflow

```text
                    LifeSync
                       |
          +------------+------------+
          |                         |
       Donor                     Recipient
          |                         |
    Registration              Registration/Login
          |                         |
          +------------+------------+
                       |
                 Donor Matching
                       |
          +------------+------------+
          |            |            |
      Compatibility  Distance    Medical Data
          |            |            |
          +------------+------------+
                       |
                 Matching Results
```

---

## Main Components

### Donor Management
The donor interface allows donor information to be entered and managed through a graphical Qt interface. Donor information includes details required for matching and identification.

### Recipient Management
The recipient workflow provides an interface for recipient-related operations and accessing donor matching functionality.

### Donor Matching
The donor matching interface presents available donor information together with matching-related details such as:
- Match score
- Distance
- Donor name
- Contact information
- Blood group
- Available organs
- Hospital
- Gender

This allows potential donor matches to be reviewed through a centralized interface.

### Facts & Information
The application also contains an informational section providing facts and awareness-related content about organ donation.

---

## Project Structure

```text
LifeSync/
│
├── main.cpp
│
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
│
├── donor_page.cpp
├── donor_page.h
├── donor_page.ui
│
├── donormatchwindow.cpp
├── donormatchwindow.h
├── donormatchwindow.ui
│
├── factswindow.cpp
├── factswindow.h
├── factswindow.ui
│
├── resource.qrc
├── LifeSync.pro
└── LifeSync_en_GB.ts
```

---

## Technologies

| Category | Technology |
| :--- | :--- |
| **Language** | C++ |
| **GUI Framework** | Qt |
| **UI Design** | Qt Designer |
| **Build System** | Qt qmake |
| **Application Type** | Desktop Application |

---

## Requirements

- C++ compiler
- Qt
- Qt Creator or another Qt-compatible development environment

---

## Running the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/NithiishSD/LifeSync.git
   cd LifeSync
   ```

2. **Open the project using Qt Creator:**
   Open `LifeSync.pro` in Qt Creator.

3. **Build and Run:**
   Configure the appropriate Qt kit, build the application, and run the generated executable.

---

## User Interface

The application contains separate interfaces for:
- Main application navigation
- Donor management
- Donor matching
- Information/facts

The `.ui` files define the Qt graphical interfaces.

---

## Technical Highlights

- Modular Qt desktop application
- C++ object-oriented implementation
- Multiple independent UI modules
- Donor and recipient workflows
- Matching-result presentation
- Qt resource management
- Internationalization support through Qt translation files

---

## Future Improvements

- Integrate a persistent database
- Add secure authentication
- Add advanced medical compatibility filtering
- Integrate real-time donor availability
- Add hospital-distance calculation
- Add automated notifications for matching donors
- Introduce role-based access for hospitals and administrators
- Add cloud-based synchronization

---

## License

This project is intended for educational and academic use.
