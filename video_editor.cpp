#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to write video frames from one capture to writer
void writeFrames(VideoCapture &cap, VideoWriter &writer, int startFrame = 0, int endFrame = -1) {
    int frameCount = 0;
    Mat frame;
    while (cap.read(frame)) {
        if (frameCount >= startFrame && (endFrame == -1 || frameCount <= endFrame)) {
            writer.write(frame);
        }
        frameCount++;
        if (endFrame != -1 && frameCount > endFrame) break;
    }
}

int main() {
    string mainVideoPath = "main_video.mp4";
    string insertVideoPath = "insert_video.mp4";
    string outputVideoPath = "final_output.mp4";

    // Open main video
    VideoCapture mainCap(mainVideoPath);
    if (!mainCap.isOpened()) {
        cerr << "Error: Cannot open main video file." << endl;
        return -1;
    }

    // Open insert video
    VideoCapture insertCap(insertVideoPath);
    if (!insertCap.isOpened()) {
        cerr << "Error: Cannot open insert video file." << endl;
        return -1;
    }

    // Get video properties from main video
    int width = (int)mainCap.get(CAP_PROP_FRAME_WIDTH);
    int height = (int)mainCap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = mainCap.get(CAP_PROP_FPS);
    int fourcc = VideoWriter::fourcc('m','p','4','v');

    // Create writer
    VideoWriter writer(outputVideoPath, fourcc, fps, Size(width, height));
    if (!writer.isOpened()) {
        cerr << "Error: Cannot open video writer." << endl;
        return -1;
    }

    // Decide cut position (e.g., cut at 5 seconds)
    double cutTime = 5.0;
    int cutFrame = (int)(cutTime * fps);

    cout << "Processing video..." << endl;

    // 1. Write first part of main video up to cutFrame
    writeFrames(mainCap, writer, 0, cutFrame);

    // 2. Write insert video entirely
    writeFrames(insertCap, writer);

    // 3. Write remaining part of main video
    mainCap.set(CAP_PROP_POS_FRAMES, cutFrame + 1); // jump to cut point
    writeFrames(mainCap, writer);

    cout << "Final video saved as: " << outputVideoPath << endl;

    return 0;
}
