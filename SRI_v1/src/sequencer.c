#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequencer.h"
#include "main.h"
#include "event_queue.h"
#include "settings.h"
#include "event_handler.h"

/*! \brief Function to be called if the ptt input is pressed */
void sequencer_activate(void) {
  event_add_message((void *)event_handler_ptt_radio_activate, settings_get_ptt_radio_pre_delay()*10, SEQUENCER_EVENT_TYPE_PTT_RADIO_ON, EVENT_PRIORITY_LEVEL_REALTIME);
  event_add_message((void *)event_handler_ptt_amp_activate, settings_get_ptt_amp_pre_delay()*10, SEQUENCER_EVENT_TYPE_PTT_AMP_ON, EVENT_PRIORITY_LEVEL_REALTIME);
  event_add_message((void *)event_handler_ptt_inhibit_activate, settings_get_ptt_inhibit_pre_delay()*10, SEQUENCER_EVENT_TYPE_PTT_INHIBIT_ON, EVENT_PRIORITY_LEVEL_REALTIME);
  event_add_message((void *)event_handler_ptt_ant_activate, settings_get_ptt_antenna_pre_delay()*10, SEQUENCER_EVENT_TYPE_PTT_ANT_ON, EVENT_PRIORITY_LEVEL_REALTIME);
}

/*! \brief Function to be called if the ptt input is released */
void sequencer_deactivate(void) {
  uint8_t temp_time = 0;

  //Checks so that the sequencer wasn't released premature, if it was, we drop the message to PTT the radio, amp, inhibit or antenna
  //That way if we accidentally press for example the footswitch shortly we don't need to go through the sequencer cycle if the
  //delays are longer than the footswitch was pressed (not very likely though)

  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_RADIO_ON) == 0) {
    event_add_message((void *)event_handler_ptt_radio_deactivate, settings_get_ptt_radio_post_delay()*10, SEQUENCER_EVENT_TYPE_PTT_RADIO_OFF, EVENT_PRIORITY_LEVEL_REALTIME);
    temp_time = settings_get_ptt_radio_post_delay();
  }

  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_AMP_ON) == 0) {
    event_add_message((void *)event_handler_ptt_amp_deactivate, settings_get_ptt_amp_post_delay()*10, SEQUENCER_EVENT_TYPE_PTT_AMP_OFF, EVENT_PRIORITY_LEVEL_REALTIME);

    if (settings_get_ptt_inhibit_post_delay() > temp_time)
      temp_time = settings_get_ptt_inhibit_post_delay();
  }

  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_INHIBIT_ON) == 0) {
    event_add_message((void *)event_handler_ptt_inhibit_deactivate, settings_get_ptt_inhibit_post_delay()*10, SEQUENCER_EVENT_TYPE_PTT_INHIBIT_OFF, EVENT_PRIORITY_LEVEL_REALTIME);

    if (settings_get_ptt_inhibit_post_delay() > temp_time)
      temp_time = settings_get_ptt_inhibit_post_delay();
  }

  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_AMP_ON) == 0) {
    event_add_message((void *)event_handler_ptt_ant_deactivate, settings_get_ptt_antenna_post_delay()*10, SEQUENCER_EVENT_TYPE_PTT_ANT_OFF, EVENT_PRIORITY_LEVEL_REALTIME);

  if (settings_get_ptt_antenna_post_delay() > temp_time)
    temp_time = settings_get_ptt_antenna_post_delay();
  }
}

void sequencer_lock_all(void) {
/*  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_RADIO_ON) == 0) {
    event_add_message((void *)radio_ptt_deactive, ptt_sequencer.footswitch.radio_post_delay * 10, SEQUENCER_EVENT_TYPE_PTT_RADIO_OFF);
  }
  
  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_AMP_ON) == 0) {
    event_add_message((void *)radio_amp_ptt_deactive, ptt_sequencer.footswitch.amp_post_delay * 10, SEQUENCER_EVENT_TYPE_PTT_AMP_OFF);
  }
  
  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_TX_ACTIVE_ON) == 0) {
    event_add_message((void *)radio_tx_deactive, ptt_sequencer.footswitch.antennas_post_delay * 10, SEQUENCER_EVENT_TYPE_PTT_TX_ACTIVE_OFF);
  }
      
  if (event_queue_drop_id(SEQUENCER_EVENT_TYPE_PTT_INHIBIT_ON) == 0) {
    if ((ptt_sequencer.ptt_input & (1<<PTT_INPUT_INHIBIT_POLARITY)) == 0) //Inhibit polarity = active low
      event_add_message((void *)radio_inhibit_high, ptt_sequencer.footswitch.inhibit_post_delay * 10, SEQUENCER_EVENT_TYPE_PTT_INHIBIT_OFF);
    else
      event_add_message((void *)radio_inhibit_low, ptt_sequencer.footswitch.inhibit_post_delay * 10, SEQUENCER_EVENT_TYPE_PTT_INHIBIT_OFF);
  }*/
}
