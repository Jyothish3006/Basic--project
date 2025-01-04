import cv2
import face_recognition
import sqlite3
from datetime import datetime

# Database Setup
def initialize_database():
    conn = sqlite3.connect("attendance.db")
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS attendance (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            date TEXT,
            time TEXT
        )
    """)
    conn.commit()
    conn.close()

def log_attendance(name):
    conn = sqlite3.connect("attendance.db")
    cursor = conn.cursor()
    now = datetime.now()
    date = now.strftime("%Y-%m-%d")
    time = now.strftime("%H:%M:%S")
    cursor.execute("INSERT INTO attendance (name, date, time) VALUES (?, ?, ?)", (name, date, time))
    conn.commit()
    conn.close()

# Load Known Faces
known_faces = []
known_names = []

def load_known_faces():
    global known_faces, known_names
    # Add known faces (Images should be pre-stored in a "known_faces" folder)
    # Example: known_faces/john.jpg
    known_face_names = ["John", "Alice"]
    for name in known_face_names:
        image = face_recognition.load_image_file(f"known_faces/{name}.jpg")
        encoding = face_recognition.face_encodings(image)[0]
        known_faces.append(encoding)
        known_names.append(name)

# Face Recognition
def recognize_faces():
    video_capture = cv2.VideoCapture(0)  # Use webcam

    while True:
        ret, frame = video_capture.read()
        if not ret:
            break

        # Convert the frame to RGB
        rgb_frame = frame[:, :, ::-1]

        # Find all face locations and encodings in the frame
        face_locations = face_recognition.face_locations(rgb_frame)
        face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

        for face_encoding, face_location in zip(face_encodings, face_locations):
            matches = face_recognition.compare_faces(known_faces, face_encoding)
            name = "Unknown"

            # Use the first match found
            if True in matches:
                match_index = matches.index(True)
                name = known_names[match_index]

            # Log attendance if the person is recognized
            if name != "Unknown":
                log_attendance(name)

            # Draw a rectangle around the face
            top, right, bottom, left = face_location
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 255, 0), 2)
            cv2.putText(frame, name, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 255, 255), 2)

        # Display the video feed
        cv2.imshow("Face Recognition", frame)

        # Break the loop with 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    video_capture.release()
    cv2.destroyAllWindows()

# Main Function
if __name__ == "__main__":
    initialize_database()
    load_known_faces()
    recognize_faces()
