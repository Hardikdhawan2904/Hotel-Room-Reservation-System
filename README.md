# 🏨 Hotel Reservation System

A **C-based Hotel Room Reservation System** that allows users to **reserve, cancel, check, and display room reservations** while managing a **waitlist** for fully booked rooms.

## 🚀 Features
- **🛏️ Reserve a Room:** Allows guests to reserve available rooms.
- **⛔ Cancel Reservation:** Cancel an existing reservation, automatically assigning rooms to waitlisted guests.
- **📋 Check Room Status:** View if a room is reserved or available.
- **📜 Display Reserved Rooms:** Lists all currently occupied rooms and their guests.
- **📝 Waitlist Management:** Guests are added to a waitlist when rooms are full and reassigned upon cancellations.

## 🛠️ Installation & Compilation

### 1️⃣ Clone the Repository

git clone https://github.com/yourusername/hotel-reservation-system.git

cd hotel-reservation-system

2️⃣ Compile the Program
Ensure you have GCC installed. Then, run:

gcc hotel_reservation.c -o hotel_reservation.exe

(Replace hotel_reservation.c with your actual filename if different.)

3️⃣ Run the Program

./hotel_reservation.exe  # On Linux/Mac

hotel_reservation.exe    # On Windows
