// Reads a video file and outputs its frames to a new file
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("video-copy SRC DEST\n");
        return 1;
    }

    cv::VideoCapture video(argv[1]);
    if (!video.isOpened()) {
        printf("Failed to open video %s\n", argv[1]);
        return 1;
    }

    cv::Size frame_size = cv::Size((int) video.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                                   (int) video.get(CV_CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter copy(argv[2], video.get(CV_CAP_PROP_FOURCC),
                        video.get(CV_CAP_PROP_FPS), frame_size);

    while (true) {
        cv::Mat frame;
        if (!video.read(frame))
            break;

        copy.write(frame);
    }
    return 0;
}
