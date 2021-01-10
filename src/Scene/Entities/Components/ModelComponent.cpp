#include "ModelComponent.h"
#include "../../../Rendering/Textures/Material.h"
#include "../../../Rendering/Renderer.h"
#include "../../../Core/TextureManager.h"
void ModelComponent::Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform)
{
    Renderer::m_Shader->SetUniformMat4f("u_View", view);
    Renderer::m_Shader->SetUniformMat4f("u_Projection", projection);
    Renderer::m_Shader->SetUniformMat4f("u_Model", transform);
    for (auto m : meshes) {
        m.Draw(projection, view, transform);
    }
}

void ModelComponent::LoadModel(std::string path)
{
    Assimp::Importer import;
    import.SetPropertyFloat("PP_GSN_MAX_SMOOTHING_ANGLE", 90);
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        printf("ERROR::ASSIMP::{0}", import.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/')) + "/";

    ProcessNode(scene->mRootNode, scene);
}

void ModelComponent::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh ModelComponent::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.texture = 1.0f;

        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;

        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
        }
        else
            vertex.uv = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        //newMaterial->SetAlbedo(LoadMaterialTextures(material, aiTextureType_DIFFUSE).at(0));
        //new Texture()
        //if(material->GetTextureCount(aiTextureType_METALNESS) > 0)
        //    newMaterial->SetMetalness(LoadMaterialTextures(material, aiTextureType_METALNESS).at(0));
        //if (material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0)
        //    newMaterial->SetRoughness(LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS).at(0));
        //if (material->GetTextureCount(aiTextureType_AMBIENT) > 0)
        //    newMaterial->SetAO(LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION).at(0));
        //newMaterial->SetDisplacement(&LoadMaterialTextures(material, aiTextureType_DISPLACEMENT).at(0));

        //newMaterial->SetMetalness(new Texture("Res/Models/Cerberus/Textures/Cerberus_M.tga"));

        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        Material* newMaterial = new Material(TextureManager::Get()->GetTexture(directory + str.C_Str()));

        material->GetTexture(aiTextureType_NORMALS, 0, &str);
        newMaterial->SetNormal(TextureManager::Get()->GetTexture(directory + str.C_Str()));

        material->GetTexture(aiTextureType_METALNESS, 0, &str);
        newMaterial->SetMetalness(TextureManager::Get()->GetTexture(directory + str.C_Str()));

        material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &str);
        newMaterial->SetRoughness(TextureManager::Get()->GetTexture(directory + str.C_Str()));

        material->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &str);
        newMaterial->SetAO(TextureManager::Get()->GetTexture(directory + str.C_Str()));
        //newMaterial->SetRoughness(TextureManager::Get()->GetTexture("Res/Models/Cerberus/Textures/Cerberus_R.tga"));
        //newMaterial->SetMetalness(TextureManager::Get()->GetTexture("Res/Models/Cerberus/Textures/Cerberus_M.tga"));
        //newMaterial->SetAO(TextureManager::Get()->GetTexture("Res/Models/Cerberus/Textures/Raw/Cerberus_AO.tga"));
        //std::vector<Texture> diffuseMaps = ;
        //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        //
        //std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS);
        //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        //
        //std::vector<Texture> metalMaps = LoadMaterialTextures(material, aiTextureType_METALNESS);
        //textures.insert(textures.end(), metalMaps.begin(), metalMaps.end());
        //
        //std::vector<Texture> roughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS);
        //textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());
        //
        //std::vector<Texture> aoMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION);
        //textures.insert(textures.end(), aoMaps.begin(), aoMaps.end());
        return Mesh(vertices, indices, newMaterial);
    }

   
}

std::vector<Texture*> ModelComponent::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    std::vector<Texture*> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string fixedStr = std::string(str.C_Str());
        //std::string newfixedStr = fixedStr.replace(fixedStr.find("\\"), fixedStr.end(), "\\", "/");

        Texture* texture = new Texture(directory + fixedStr);
        textures.push_back(texture);
    }
    return textures;
}
