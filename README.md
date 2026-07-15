# Student Management Software

A lightweight, console-based Student Management System written in C. This program provides an interactive, menu-driven interface to manage student records efficiently, implementing full CRUD-like data workflows along with safe-deletion mechanisms using an internal Recycle Bin system.

## 🚀 Features

The application includes the following functionalities:

1. **Add Student**
   - Captures detailed records: Roll Number, Name, and Course.
   - Includes unique verification to ensure no duplicate Roll Numbers are added to active records.
2. **Display Students**
   - Renders a clean, formatted tabular matrix of all current active records.
3. **Soft Delete**
   - Prevents accidental loss of records by moving deleted student entries into a dedicated `Recycle Bin` storage area.
4. **View Recycle Bin**
   - Lists all temporarily deleted students awaiting recovery or final deletion.
5. **Recover Student**
   - Restoration function to shift records from the Recycle Bin back to the main Active database list using the unique Roll Number.
6. **Search Student**
   - High-speed lookup by Roll Number to retrieve profile data instantly.
7. **Permanent Delete**
   - Hard deletion logic that safely purges records from the Recycle Bin with a explicit user confirmation step (`y/n`).
8. **Robust Buffer Handling**
   - Input filtering techniques protect the menu selection cycle from infinite loops when invalid characters or strings are typed.

---

## 🛠️ Architecture & Memory Design

The software is configured to operate completely in-memory utilizing arrays of structures, avoiding disk storage bottlenecks for low-latency operational metrics:

- **Data Models:** Uses a nested object layout via `struct Student` matching integers and character blocks.
- **Maximum Threshold limit:** Bound to `100` simultaneous elements across active buffers as defined by `MAX_STUDENTS`.
- **State Control Flows:**
  - `active_students` array handles state tracking for standard execution blocks.
  - `recycle_bin` array isolates pending records, utilizing element shifting arrays (`j = i; j < count - 1`) to compact memory spaces on array deletions.

---

## ⚙️ Compilation & Execution

To compile and run this software locally, make sure you have a standard C compiler (like `gcc`) installed on your system.
