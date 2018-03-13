#include "filesystem.h"

void fs_list_dir(String d) {
  Dir dir = SPIFFS.openDir(d);
  Serial.println("SPIFFS directory {"+d+"} :");
  while (dir.next()) {
      Serial.print(" "); Serial.println(dir.fileName());
      Serial.println(" "); Serial.println(dir.fileSize());
  }
}

