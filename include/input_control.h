#pragma once

extern void (*process_events_func)();

void ProcessGameEvents();

void ProcessSaveEvents();
void ProcessLoadEvents();
