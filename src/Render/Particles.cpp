//
// Created by super on 07.08.2024.
//

#include "Particles.h"

#include <memory>
#include "MergedRender.h"
#include "SystemAdapter.h"

std::shared_ptr<Shader> CircleShader {};
std::shared_ptr<Shader> CircleTextureShader {};

std::shared_ptr<MergedRender> CreateCircleParticles(const CircleParticlesData& pd){
    auto out = std::make_shared<MergedRender>();
    out->quard = std::make_shared<ExtendedQuard>(pd.position, pd.size, pd.size);
    out->quard->color = pd.color;
    out->setInstancing(pd.count);
    if (!pd.texture->IsNull())
    {
        pd.texture->load();
        if (!CircleTextureShader){
            CircleTextureShader = Shaders::CreateShader();
            CircleTextureShader->setFragmentShader(Shaders::TextureFragmentShader);
            CircleTextureShader->setVertexShader("#version 330 core\n#ifdef GL_ES\nprecision mediump float;\n#endif\nlayout (location = 0) in vec3 position; layout (location = 1) in vec4 color; layout (location = 2) in vec2 texCoord; uniform mat4 projection; uniform float time; uniform float lifetime; uniform float distdifference; out vec2 TexCoord; out vec4 Color; void main(){float m = time + gl_InstanceID / distdifference; float dist = (m - int(m)) * lifetime; vec2 circle = vec2(dist*cos(gl_InstanceID), dist*sin(gl_InstanceID)); gl_Position = projection * (vec4(position.xy + circle, position.z, 1)); TexCoord = texCoord; Color = color; }");
        }
        out->shader = CircleTextureShader;
    } else {
        if (!CircleShader){
            CircleShader = Shaders::CreateShader();
            CircleShader->setVertexShader("#version 330 core\n#ifdef GL_ES\nprecision mediump float;\n#endif\nlayout (location = 0) in vec3 position; layout (location = 1) in vec4 color; layout (location = 2) in vec2 texCoord; uniform mat4 projection; uniform float time; uniform float lifetime; uniform float distdifference; out vec2 TexCoord; out vec4 Color; void main(){float m = time + gl_InstanceID / distdifference; float dist = (m - int(m)) * lifetime; vec2 circle = vec2(dist*cos(gl_InstanceID), dist*sin(gl_InstanceID)); gl_Position = projection * (vec4(position.xy + circle, position.z, 1)); TexCoord = texCoord; Color = color; }");
        }
        out->shader = CircleShader;
    }
    out->load();
    return out;
}
void UseCircleParticles(std::shared_ptr<MergedRender>& r, const CircleParticlesData& pd, glm::mat4 mat){
    r->shader->use();
    r->shader->SetUniform(glfwGetTime(), "time");
    r->shader->SetUniform(mat, "projection");
    r->shader->SetUniform(pd.lifetime, "lifetime");
    r->shader->SetUniform(pd.distdifference, "distdifference");
    r->useClear();
}