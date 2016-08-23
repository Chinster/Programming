// Merges all source videos into a single file.
// Only works with videos with the same specification.
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>

int appendVideo(cv::VideoWriter &out, int i, char *argv[])
{
    cv::VideoCapture video(argv[i]);
    if (!video.isOpened()) {
        printf("Failed to open video %s\n", argv[1]);
        return 1;
    }

    while (true) {
        cv::Mat frame;
        if (!video.read(frame))
            break;

        out.write(frame);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("video-copy SRC... DEST\n");
        return 1;
    }

    // Open first video
    cv::VideoCapture video(argv[1]);
    if (!video.isOpened()) {
        printf("Failed to open video %s\n", argv[1]);
        return 1;
    }

    cv::Size frame_size = cv::Size((int) video.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                                   (int) video.get(CV_CAP_PROP_FRAME_HEIGHT));
    cv::VideoWriter out(argv[argc - 1], video.get(CV_CAP_PROP_FOURCC),
                        video.get(CV_CAP_PROP_FPS), frame_size);

    for (int i = 1; i < argc - 1; i++) {
        if (appendVideo(out, i, argv) != 0) {
            printf("Failed to append video %s\n", argv[i]);
            return 2;
        }
    }
    return 0;
}
