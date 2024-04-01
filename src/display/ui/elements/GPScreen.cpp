#include "GPScreen.h"

void GPScreen::draw() {
    getRenderer()->clearScreen();

    // draw the display list
    if ( displayList.size() > 0 ) {
        std::sort(displayList.begin(), displayList.end(), [](std::unique_ptr<GPWidget>& a, std::unique_ptr<GPWidget>& b){ return a->getPriority() > b->getPriority(); });
        for(std::vector<std::unique_ptr<GPWidget>>::iterator it = displayList.begin(); it != displayList.end(); ++it) {
            (*it)->draw();
        }
    }
    drawScreen();
    getRenderer()->render();
}

int8_t GPScreen::update() {
    return 0;
}

void GPScreen::clear() {
    if (displayList.size() > 0) {
        displayList.clear();
        displayList.shrink_to_fit();
    }
}
std::string GPScreen::intToMm(int16_t num) {
		const int8_t bufferSize = 20;
    char buffer[bufferSize];
    int whole_part = num / 100;
    int remainder = num % 100;
    std::snprintf(buffer, bufferSize, "%d.%02dmm", whole_part, remainder);

    return std::string(buffer);
}

void GPScreen::drawAnalogKeyOptions() {
    const AnalogKeyOptions& analogKeyOptions = Storage::getInstance().getAddonOptions().analogKeyOptions;
    std::string line1 = "";
    std::string line2 = "";

    line1 += "AM:";

    switch (analogKeyOptions.actuationOptions.actuationMode) {
        case 0:
            line1 += "SA      ";
            break;
        case 1:
            line1 += "RT      ";
            break;
        case 2:
            line1 += "CRT     ";
            break;
        default:
            break;
    }
    line1 += "AP:" + intToMm(analogKeyOptions.actuationOptions.actuationPoint);

    getRenderer()->drawText(0, 1, line1);

    if (analogKeyOptions.actuationOptions.actuationMode != 0) {
        line2 += "PS:" + intToMm(analogKeyOptions.actuationOptions.pressSensitivity);
        line2 += "  RS:" + intToMm(analogKeyOptions.actuationOptions.releaseSensitivity);
        getRenderer()->drawText(0, 2, line2);
    }
}
