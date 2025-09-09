FROM python:3.11-slim

# Install dependencies
RUN apt-get update && apt-get install -y g++ cmake libopencv-dev python3-opencv && apt-get clean

# Set working directory
WORKDIR /app

# Copy files
COPY . .

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Compile C++ video editor
RUN g++ video_editor.cpp -o video_editor `pkg-config --cflags --libs opencv4`

# Command to run both steps
CMD ["sh", "-c", "./video_editor && python send_to_telegram.py"]
