//
// Created by super on 07.08.2024.
//

#include "Particles.h"

#include <memory>
#include "MergedRender.h"
#include "SystemAdapter.h"

std::shared_ptr<MergedRender> CreateParticles(const ParticlesData& pd){
    auto out = std::make_shared<MergedRender>();
    out->quard = std::make_shared<ExtendedQuard>(pd.position, pd.size, pd.size);
    out->setInstancing(pd.count);
    auto str = SystemAdapter::ReadAll(SystemAdapter::ExePath() + "Instancing_test.vert");
    out->setVertexShader(str.c_str());
    out->load();
    return out;
}
void UseParticles(std::shared_ptr<MergedRender>& r, const ParticlesData& pd, glm::mat4 mat){
    r->useProgramm();
    r->SetUniform(glfwGetTime(), "time");
    r->SetUniform(mat, "projection");
    r->SetUniform(pd.lifetime, "lifetime");
    r->SetUniform(pd.distdifference, "distdifference");
    r->useClear();
}