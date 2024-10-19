import cv2

# Initialize the HOG descriptor/person detector
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

# Open webcam feed
cap = cv2.VideoCapture(0)

def detect_human(frame):
    # Resize the frame for faster processing
    resized_frame = cv2.resize(frame, (640, 480))
    
    # Detect people in the frame
    (humans, _) = hog.detectMultiScale(resized_frame, winStride=(4, 4), padding=(8, 8), scale=1.05)
    
    # Draw rectangles around detected humans
    for (x, y, w, h) in humans:
        cv2.rectangle(resized_frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
    
    return resized_frame  # Return the processed frame with detection

while True:
    # Capture frame from webcam
    ret, frame = cap.read()
    
    if not ret:
        print("Failed to grab frame")
        break

    # Detect humans in the frame
    processed_frame = detect_human(frame)

    # Display the webcam feed with detections
    cv2.imshow("Human Detection", processed_frame)

    # Break the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close OpenCV windows
cap.release()
cv2.destroyAllWindows()
