# Electrical Fault Logging and Analysis System

## 📖 Project Overview
This project is part of the BEE 208 C++ Programming course at Accra Technical University.  
It focuses on designing a **menu-driven application** that records electrical fault cases, classifies their severity, and generates a structured report for maintenance decision-making.

## 🎯 Problem Statement
Electrical faults in laboratories, hostels, and workshops are often reported informally without proper documentation.  
This makes it difficult to track recurring issues and plan preventive maintenance.  
Our solution provides a structured way to log faults, validate readings, classify severity, and save reports for future reference.

## 🛠 Aim
To develop a C++ program that:
- Records fault details (ID, location, type, voltage, current, action taken)
- Classifies severity using decision rules
- Summarizes fault categories
- Saves a complete report to `electrical_fault_report.txt`

## ✅ Objectives
1. Create a menu-driven C++ program for fault logging.  
2. Validate voltage and current readings (no negative values).  
3. Classify severity as Minor, Moderate, Serious, or Critical.  
4. Display fault reports and summaries.  
5. Save all records and summaries to a text file.  
6. Use GitHub for collaboration and submission.  

## ⚡ Severity Classification Rules
- **Critical**: Short Circuit, Burning Smell, Electric Shock  
- **Serious**: Voltage <180V or >250V, Current >15A  
- **Moderate**: Loose Connection, Flickering Light, Damaged Socket  
- **Minor**: Routine complaint with normal readings  
- **Invalid**: Negative voltage or current values  

## 💻 C++ Concepts Applied
- Classes and objects for fault records  
- Functions for validation, classification, display, and file saving  
- Vectors to store multiple records  
- Decision statements (`if`, `else if`, `else`)  
- Loops for multiple entries  
- File handling with `ofstream`  

## 📂 Repository Structure
