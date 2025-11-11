# Midterm Project for Embedded System Design

## Music Player UI Mockup

| Element      | Widget              | Description                              |
| ------------ | ------------------- | ---------------------------------------- |
| Album Art    | `lv_img`            | Show a **rotating** image (album cover)        |
| Song Title  (Done)| `lv_label`          | Large bold font **chyron** (e.g., “Night Sky”)      |
| Artist Name  | `lv_label`          | Smaller gray text below title            |
| Progress Bar (Done) | `lv_slider`         | Show playback progress                   |
| Time labels (Done) | `lv_label`          | “0:00” and “3:45” at both ends of slider |
| Buttons    (Done)  | `lv_btn` + `lv_img` | Play / Pause / Next / Prev buttons       |
| Background (Done)  | `lv_obj`            | Apply gradient or dark theme             |

## Additional Idea

"Translate on Scroll" from lvgl example for track queue

## Implementation Steps Completed

Sequence of UI features implemented (see `lvgl/examples/mainfunction.c`):

1. Gradient Background:

  - Create a Radial Gradient Background with white center to grey edge.

2. Time Labels:

  - Convert the time label into mm:ss format in slider event.
  - Set the time label on the left side under the progress bar. And the total time at the right side under the progress bar.

3. Progress Bar (Slider):

  - Change the color of track into medium gray and indicator into light gray.
  - Hide the knob by reducing its opacity.

4. Control Buttons:

  - Added Prev / Pause / Next buttons under the slider.
  - Styled the normal button into circular shape, transparent background, and no border.
  - Cover the styled buttons with icon's png transfered C code.

5. Customize Cursor:

  - Add my own cursor by transfering the cursor icon from png into c code online with format `ARGB888` which allows opacity, and replace the cursors source file.

6. Improve Progress Bar (Slider): (I found some time will not be displayed in the progress bar)
  - Set the slider range to 1000, allow every second in the slider can be shown.
  - Modify the converting code of slider event


7. Button Event:

  - Next and prev will now send the progress bar to 0, also update the time label.
  - Pause will change the opacity of the indicator.

8. Song Title Ticker

  - If the song title string is longer than the slider box, it will loop like a ticker.
  - Next and Pause will reset the song title ticker.
  - 8 seconds between each loop.

9. Improve overall UI

  - Radial Gradient Background extend with the window
  - Progress bar and all the label and buttons stay at center no matter how the window is resized.

10. Improve Code

  - Reorder function and add new comment.

11. Upgrade Pause Button

  - The icon of the pause button now switch between play and pause.

12.

## Next Enhancements (Ideas)

- Rotating album art (`lv_img` with animation).
- Track queue scroll effect ("Translate on Scroll" idea above).
