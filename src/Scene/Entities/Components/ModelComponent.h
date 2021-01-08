#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <vector>
#include "../../../Rendering/Mesh/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelComponent
{
public:
    ModelComponent()
    {
        //loadModel(path);
    }
    void LoadModel(std::string path);
    void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;

    
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
};