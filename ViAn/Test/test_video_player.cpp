#include "test_video_player.h"
#include <thread>
#include <QMutex>
#include <QWaitCondition>

/**
 * @brief test_video_player::test_video_player
 * constructor
 * @param parent
 */
test_video_player::test_video_player(QObject *parent) : QObject(parent) {
    QMutex mutex;
    QWaitCondition wait;
    mvideo = new video_player(&mutex, &wait);
}

/**
 * @brief test_video_player::test_load_video
 */
void test_video_player::test_load_video() {
    string working_filename = "seq_01.mp4";
    string non_existing_filename = "ex.biz";
    string existing_non_video = "Makefile";

    QVERIFY(mvideo->capture.open(working_filename));
    mvideo->frame_rate = mvideo->capture.get(CV_CAP_PROP_FPS);
    mvideo->num_frames = mvideo->capture.get(cv::CAP_PROP_FRAME_COUNT);
    mvideo->video_paused = false;

    QVERIFY(mvideo->capture.isOpened());

}

/**
 * @brief test_video_player::test_is_paused
 */
void test_video_player::test_is_paused() {
    mvideo->video_paused = false;
    QVERIFY(!mvideo->is_paused());
    mvideo->video_paused = true;
    QVERIFY(mvideo->is_paused());
}

/**
 * @brief test_video_player::test_get_num_frames
 */
void test_video_player::test_get_num_frames() {
    QVERIFY(mvideo->capture.get(cv::CAP_PROP_FRAME_COUNT) == mvideo->get_num_frames());
}

/**
 * @brief test_video_player::test_set_frame_width
 */
void test_video_player::test_set_frame_width() {
    mvideo->set_frame_width(50);
    QVERIFY(mvideo->frame_width == 50);
}

/**
 * @brief test_video_player::test_set_frame_height
 */
void test_video_player::test_set_frame_height() {
    mvideo->set_frame_height(50);
    QVERIFY(mvideo->frame_height == 50);
}

/**
 * @brief test_video_player::test_set_current_frame
 */
void test_video_player::test_set_current_frame() {
    mvideo->set_current_frame_num(100);
    QVERIFY(mvideo->get_current_frame_num() == 100);
    mvideo->set_current_frame_num(10);
    mvideo->set_current_frame_num(-10);
    QVERIFY(mvideo->get_current_frame_num() == 10);
}

/**
 * @brief test_video_player::test_next_frame
 */
void test_video_player::test_next_frame() {
    mvideo->set_current_frame_num(100);
    mvideo->next_frame();
    QVERIFY(mvideo->get_current_frame_num() == 101);
}

/**
 * @brief test_video_player::test_previous_frame
 */
void test_video_player::test_previous_frame() {
    mvideo->set_current_frame_num(100);
    mvideo->previous_frame();
    QVERIFY(mvideo->get_current_frame_num() == 99);
}

/**
 * @brief test_video_player::test_inc_playback_speed
 */
void test_video_player::test_inc_playback_speed(){
    mvideo->set_speed_multiplier(1);
    QVERIFY(mvideo->get_speed_multiplier() == 1);

    mvideo->inc_playback_speed();
    QVERIFY(mvideo->get_speed_multiplier() == 0.5);

    mvideo->set_speed_multiplier(1.0/16);
    mvideo->inc_playback_speed();
    QVERIFY(mvideo->get_speed_multiplier() == 1.0/16);
}

/**
 * @brief test_video_player::test_dec_playback_speed
 */
void test_video_player::test_dec_playback_speed(){
    mvideo->set_speed_multiplier(1);
    QVERIFY(mvideo->get_speed_multiplier() == 1);

    mvideo->dec_playback_speed();
    QVERIFY(mvideo->get_speed_multiplier() == 2);

    mvideo->set_speed_multiplier(16);
    mvideo->dec_playback_speed();
    QVERIFY(mvideo->get_speed_multiplier() == 16);
}

/**
 * @brief test_toggle_overlay
 */
void test_video_player::test_toggle_overlay() {
    mvideo->on_stop_video();
    mvideo->video_overlay->set_showing_overlay(false);
    mvideo->toggle_overlay();
    QVERIFY(mvideo->is_showing_overlay());
    mvideo->toggle_overlay();
    QVERIFY(!mvideo->is_showing_overlay());
}

/**
 * @brief test_video_player::test_set_overlay_tool
 */
void test_video_player::test_set_overlay_tool() {
    mvideo->set_overlay_tool(RECTANGLE);
    QVERIFY(mvideo->video_overlay->get_shape() == RECTANGLE);
}

/**
 * @brief test_video_player::test_set_overlay_colour
 */
void test_video_player::test_set_overlay_colour() {
    mvideo->set_overlay_colour(Qt::black);
    QVERIFY(mvideo->video_overlay->get_colour() == Qt::black);
}

/**
 * @brief test_video_player::test_set_play_video
 */
void test_video_player::test_set_play_video() {
    mvideo->video_paused = true;
    mvideo-> video_stopped = true;
    mvideo->on_play_video();
    QVERIFY(!mvideo->video_paused);
    QVERIFY(!mvideo->video_stopped);
}

/**
 * @brief test_video_player::test_set_paused_video
 */
void test_video_player::test_set_pause_video() {
    mvideo->video_paused = false;
    mvideo->on_pause_video();
    QVERIFY(mvideo->video_paused);
}

/**
 * @brief test_video_player::test_set_stop_video
 */
void test_video_player::test_set_stop_video() {
    mvideo->video_paused = true;
    mvideo->video_stopped = false;
    mvideo->on_stop_video();
    QVERIFY(!mvideo->video_paused);
    QVERIFY(mvideo->get_current_frame_num() == 0);
    QVERIFY(mvideo->video_stopped);
}
