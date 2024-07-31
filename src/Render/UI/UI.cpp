//
// Created by super on 23.07.2024.
//

#include <glm/ext/matrix_clip_space.hpp>
#include "UI.h"

glm::mat4 UI::Matrix(int width, int height) {
    if ((float) width > (float) height)
        return glm::ortho(-1.0 * ((float) width/(float) height), 1.0 * ((float) width/(float) height), -1.0, 1.0, -1.0, 1.0);
    else
        return glm::ortho(-1.0, 1.0, -1.0 * ((float) height/(float) width), 1.0 * ((float) height/(float) width), -1.0, 1.0);
}

void UI::DarkerBackground(std::unique_ptr<MergedRender>& m) {
    m->quard.reset(new ExtendedQuard({-2,-2},4,4));
    m->quard->color = {0.,0.,0.,.5};
    m->setSpeed(MergedRender::SpeedContent::STATIC);
}

glm::vec2 UI::vector_to_uicoords(double xpos, double ypos){
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    if ((float) width > (float) height)
        return {((float) width/(float) height * 2) /((float) width / xpos) - ((float) width/(float) height),ypos / height * -2 + 1};
    else
        return {xpos / width * 2 - 1,(((float) height/(float) width * 2) /((float) height / ypos) - ((float) height/(float) width)) * -1};
}
