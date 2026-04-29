# F-Code Event Staff Management System

A terminal-based application written in **C language** for managing event personnel within the F-Code Academic Club at FPT University Ho Chi Minh City.



## Project Overview

F-Code Academic Club organizes many events every year, from internal workshops to large competitions. Previously, all data was managed manually using Google Sheets and social media, which caused inefficiency and lack of centralized control.

This project aims to build a **centralized management system** that allows:

* Managing events
* Assigning personnel to events
* Tracking event progress
* Saving and loading data from files



## Features

### Authentication

* Login system
* Change password
* Lock account after 3 failed login attempts

### Staff Functions

* View personal profile
* View assigned events
* View participation history

### Event Management (Admin only)

* Create new event
* Edit event information
* Delete event
* Search event
* Update event status

### Staff Assignment

* Add personnel to event
* Remove personnel
* Edit roles and tasks

### Advanced Features (In Progress)

* Event statistics
* Sorting and searching events
* Console UI with colors (ANSI)

---

## Tech Stack

* **Programming Language:** C
* **Libraries:** stdio.h, stdlib.h, string.h, time.h
* **Data Storage:** `.dat` files
* **Build Tool:** Makefile

---

## Installation & Run

### 1. Clone repository

git clone https://github.com/nolan1612/F-Code-s_event_personnel_management_project
cd F-Code-s_event_personnel_management_project

### 2. Compile

make

### 3. Run

./main

👉 Or using gcc:
gcc src/*.c -Iincludes -o main
./main

---

## Project Structure
```bash
├── src/                # Source code
├── includes/           # Header files
├── data/               # Data storage
│   ├── events.dat
│   └── accounts.dat
├── Makefile
└── README.md
---

## System Design

### Main Modules

* auth.c / auth.h → Authentication & authorization
* event.c / event.h → Event management
* staff.c / staff.h → Staff assignment
* fileio.c / fileio.h → File operations
* utils.c / utils.h → Helper functions

---

## Data Structures

### Event

* Event ID (auto-generated)
* Name, description, location
* Start date, end date
* Status (0: Not started, 1: Ongoing, 2: Finished)
* Staff list (max 30 people)

### StaffEntry

* Student ID
* Name
* Role
* Task description

### Account

* Student ID
* Username
* Password
* Role (Admin / Member)
* Lock status
* Failed login attempts

---

## Key Logic

* Auto-save data after every operation
* Case-insensitive search
* Account lock after 3 failed login attempts
* Date validation (YYYY-MM-DD format)
* Event status flow: Not Started → Ongoing → Finished
* Prevent editing finished events
* Confirmation required when editing ongoing events

---

## Constraints

* Maximum 1,000,000 events
* Maximum 30 staff per event
* No GUI (terminal only)
* No external libraries

---

## Remaining Work

* Complete advanced features
* Fix bugs and optimize performance
* Improve Git workflow
* Add account unlock feature
* Perform large-scale testing

---

## Team Members (Catto)

| No | Name                   | Student ID | Role   |
| -- | ---------------------- | ---------- | ------ |
| 1  | Nguyen Hoang Minh Nhat | SE211601   | Leader |
| 2  | Le Minh Dang           | SE201183   | Member |
| 3  | Le Thi Minh Tam        | SE201843   | Member |
| 4  | Le Kha Huy             | SE211591   | Member |
| 5  | Le Kha Hoang           | SE211377   | Member |

---

## Project Information

* Organization: F-Code Academic Club
* Mentor: Nguyen Duc Huy
* Duration: 17/04/2026 → 17/05/2026

---

## GitHub Repository

https://github.com/nolan1612/F-Code-s_event_personnel_management_project

---

## Notes

* Ensure data files exist before running
* Always commit code with clear messages
* Follow team workflow when pushing code

---

## Contribution Guide

git checkout -b feature/your-feature
git commit -m "Add: your feature"
git push origin feature/your-feature

