#pragma once

#include "wled.h"

//This is an empty v2 usermod template. Please see the file usermod_v2_example.h in the EXAMPLE_v2 usermod folder for documentation on the functions you can use!

class UsermodDigitalClock : public Usermod {
  private:

  bool enabled;

  // length of a single segment
  int segment_length;

  // 10 Hour digits
  int h10_bot;
  int h10_bot_left;
  int h10_bot_right;
  int h10_middle;
  int h10_top_left;
  int h10_top_right;
  int h10_top;

  // 1 Hour digits
  int h1_bot;
  int h1_bot_left;
  int h1_bot_right;
  int h1_middle;
  int h1_top_left;
  int h1_top_right;
  int h1_top;

  // 10 Minute digits
  int m10_bot;
  int m10_bot_left;
  int m10_bot_right;
  int m10_middle;
  int m10_top_left;
  int m10_top_right;
  int m10_top;

  // 1 Minute digits
  int m1_bot;
  int m1_bot_left;
  int m1_bot_right;
  int m1_middle;
  int m1_top_left;
  int m1_top_right;
  int m1_top;

  // Segments to turn off
  int segment_off1;
  int segment_off2;
  int segment_off3;
  int segment_off4;
  int segment_off5;
  int segment_off6;
  int segment_off7;
  int segment_off8;
  int segment_off9;

  // Numbers to show on the display
  uint8_t segment1_number;
  uint8_t segment2_number;
  uint8_t segment3_number;
  uint8_t segment4_number;

  int current_seg;

  enum Mode { clock, timer };

  /*
   * setClockSegment turns the given Segments of the clock of, to only show the
   * numbers on the display
   */
  void setClockSegment(uint8_t num, ...) {
    va_list ap;
    va_start(ap, num);
    for (int i = 0; i < num; i++) {
      int pos = va_arg(ap, int);
      for (int j = pos; j < pos + this->segment_length; j++)
        strip.setPixelColor(j, RGBW32(0, 0, 0, 0));
    }
  }

  void setNextSegment(int *seg) {
    *seg = current_seg * segment_length;
    current_seg++;
  }

  public:
    void setup() {
      enabled = strip.getLength() >= 370;
      current_seg = 0;
      segment_length = 10;
      setNextSegment(&h10_bot);
      setNextSegment(&segment_off1);
      setNextSegment(&h1_bot);
      setNextSegment(&segment_off2);
      setNextSegment(&m10_bot);
      setNextSegment(&segment_off3);
      setNextSegment(&m1_bot);
      setNextSegment(&m1_middle);
      setNextSegment(&segment_off4);
      setNextSegment(&m10_middle);
      setNextSegment(&segment_off5);
      setNextSegment(&h1_middle);
      setNextSegment(&segment_off6);
      setNextSegment(&h10_middle);
      setNextSegment(&h10_top);
      setNextSegment(&segment_off7);
      setNextSegment(&h1_top);
      setNextSegment(&segment_off8);
      setNextSegment(&m10_top);
      setNextSegment(&segment_off9);
      setNextSegment(&m1_top);
      setNextSegment(&m1_top_right);
      setNextSegment(&m1_bot_right);
      setNextSegment(&m1_bot_left);
      setNextSegment(&m1_top_left);
      setNextSegment(&m10_top_right);
      setNextSegment(&m10_bot_right);
      setNextSegment(&m10_bot_left);
      setNextSegment(&m10_top_left);
      setNextSegment(&h1_top_right);
      setNextSegment(&h1_bot_right);
      setNextSegment(&h1_bot_left);
      setNextSegment(&h1_top_left);
      setNextSegment(&h10_top_right);
      setNextSegment(&h10_bot_right);
      setNextSegment(&h10_bot_left);
      setNextSegment(&h10_top_left);
    }

    void loop() {
      int tHour = hour(localTime);
      int tMinute = minute(localTime);

      segment1_number = tHour / 10;
      segment2_number = tHour % 10;

      segment3_number = tMinute / 10;
      segment4_number = tMinute % 10;
    }

    void handleOverlayDraw()
    {
      if (!enabled || strip.getLength() < 370)
        return;

      setClockSegment(9, segment_off1, segment_off2, segment_off3, segment_off4, segment_off5, segment_off6, segment_off7, segment_off8, segment_off9);

      switch (segment1_number) {
        case 0:
          setClockSegment(1, h10_middle);
          break;
        case 1:
          setClockSegment(5, h10_top, h10_top_left, h10_middle, h10_bot_left, h10_bot);
          break;
        case 2:
          setClockSegment(2, h10_top_left, h10_bot_right);
          break;
        case 3:
          setClockSegment(2, h10_top_left, h10_bot_left);
          break;
        case 4:
          setClockSegment(3, h10_top, h10_bot_left, h10_bot);
          break;
        case 5:
          setClockSegment(2, h10_top_right, h10_bot_left);
          break;
        case 6:
          setClockSegment(1, h10_top_right);
          break;
        case 7:
          setClockSegment(4, h10_top_left, h10_middle, h10_bot_left, h10_bot);
          break;
        case 8:
          break;
        case 9:
          setClockSegment(1, h10_bot_left);
          break;
        default:
          setClockSegment(7, h10_top, h10_top_left, h10_top_right, h10_middle, h10_bot_left, h10_bot_right, h10_bot);
          break;
      }
    switch (segment2_number) {
        case 0:
          setClockSegment(1, h1_middle);
          break;
        case 1:
          setClockSegment(5, h1_top, h1_top_left, h1_middle, h1_bot_left, h1_bot);
          break;
        case 2:
          setClockSegment(2, h1_top_left, h1_bot_right);
          break;
        case 3:
          setClockSegment(2, h1_top_left, h1_bot_left);
          break;
        case 4:
          setClockSegment(3, h1_top, h1_bot_left, h1_bot);
          break;
        case 5:
          setClockSegment(2, h1_top_right, h1_bot_left);
          break;
        case 6:
          setClockSegment(1, h1_top_right);
          break;
        case 7:
          setClockSegment(4, h1_top_left, h1_middle, h1_bot_left, h1_bot);
          break;
        case 8:
          break;
        case 9:
          setClockSegment(1, h1_bot_left);
          break;
        default:
          setClockSegment(7, h1_top, h1_top_left, h1_top_right, h1_middle, h1_bot_left, h1_bot_right, h1_bot);
          break;
      }
    switch (segment3_number) {
        case 0:
          setClockSegment(1, m10_middle);
          break;
        case 1:
          setClockSegment(5, m10_top, m10_top_left, m10_middle, m10_bot_left, m10_bot);
          break;
        case 2:
          setClockSegment(2, m10_top_left, m10_bot_right);
          break;
        case 3:
          setClockSegment(2, m10_top_left, m10_bot_left);
          break;
        case 4:
          setClockSegment(3, m10_top, m10_bot_left, m10_bot);
          break;
        case 5:
          setClockSegment(2, m10_top_right, m10_bot_left);
          break;
        case 6:
          setClockSegment(1, m10_top_right);
          break;
        case 7:
          setClockSegment(4, m10_top_left, m10_middle, m10_bot_left, m10_bot);
          break;
        case 8:
          break;
        case 9:
          setClockSegment(1, m10_bot_left);
          break;
        default:
          setClockSegment(7, m10_top, m10_top_left, m10_top_right, m10_middle, m10_bot_left, m10_bot_right, m10_bot);
          break;
      }
    switch (segment4_number) {
        case 0:
          setClockSegment(1, m1_middle);
          break;
        case 1:
          setClockSegment(5, m1_top, m1_top_left, m1_middle, m1_bot_left, m1_bot);
          break;
        case 2:
          setClockSegment(2, m1_top_left, m1_bot_right);
          break;
        case 3:
          setClockSegment(2, m1_top_left, m1_bot_left);
          break;
        case 4:
          setClockSegment(3, m1_top, m1_bot_left, m1_bot);
          break;
        case 5:
          setClockSegment(2, m1_top_right, m1_bot_left);
          break;
        case 6:
          setClockSegment(1, m1_top_right);
          break;
        case 7:
          setClockSegment(4, m1_top_left, m1_middle, m1_bot_left, m1_bot);
          break;
        case 8:
          break;
        case 9:
          setClockSegment(1, m1_bot_left);
          break;
        default:
          setClockSegment(7, m1_top, m1_top_left, m1_top_right, m1_middle, m1_bot_left, m1_bot_right, m1_bot);
          break;
      }
    }

    void addToConfig(JsonObject& root)
    {
      JsonObject top = root.createNestedObject(F("Clock"));
      top["enabled"] = enabled;
    }

    bool readFromConfig(JsonObject& root)
    {
      // default settings values could be set here (or below using the 3-argument getJsonValue()) instead of in the class definition or constructor
      // setting them inside readFromConfig() is slightly more robust, handling the rare but plausible use case of single value being missing after boot (e.g. if the cfg.json was manually edited and a value was removed)

      JsonObject top = root[F("Clock")];

      bool configComplete = !top.isNull();

      configComplete &= getJsonValue(top["enabled"], enabled);

      return configComplete;
    }
};