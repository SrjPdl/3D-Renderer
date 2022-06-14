#include "Model.h"


void Model::load(const char* filePath, uint32_t program)
{
	this->program = program;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
											 aiProcess_Triangulate			 
											|aiProcess_JoinIdenticalVertices
											);
	
	if (!scene)
	{
		std::cout<<"ERROR::FAILED_TO_LOAD:\"" << filePath << "\" : "<<importer.GetErrorString() << std::endl;
		return;
	}
	handleNode(scene->mRootNode, scene);

	handleTextMat(scene);
}

void Model::render(glm::mat4* modelMatrix)
{
	for (uint32_t i = 0; i < meshes.size(); i++)
	{
		diffuseTexture[textureIndex[i]]->Activate();
		specularTexture[textureIndex[i]]->Activate();
		materials[textureIndex[i]]->update();

		meshes[i]->update(modelMatrix);
		meshes[i]->render();
	}
}

void Model::handleNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		handleMesh(mesh, scene);
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		handleNode(node->mChildren[i], scene);
	}

}

void Model::handleMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector <float> vertices;
	std::vector <uint32_t> indices;
	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		//Vertex Position
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		if (mesh->HasNormals())
		{
			vertices.push_back(-mesh->mNormals[i].x);
			vertices.push_back(-mesh->mNormals[i].y);
			vertices.push_back(-mesh->mNormals[i].z);
		}
		else
		{
			vertices.insert(vertices.end(), { 0.f, 0.f, 0.f });
		}
		

		if (mesh->mTextureCoords[0])
		{
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}
		else
		{
			vertices.push_back(0.f);
			vertices.push_back(0.f);
		}

	}

	if (!mesh->HasNormals())
	{
		Helper::calculateVertexNormal(&vertices[0], vertices.size(), &indices[0], indices.size(), 8, 3);
	}

	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
		
	}


	Mesh* nMesh = new Mesh;
	nMesh->create(&vertices[0], vertices.size(), &indices[0], indices.size(), this->program);
	meshes.push_back(nMesh);

	textureIndex.push_back(mesh->mMaterialIndex);

}

void Model::handleTextMat(const aiScene* scene)
{
	diffuseTexture.resize(scene->mNumMaterials);
	specularTexture.resize(scene->mNumMaterials);

	for (uint32_t i = 0; i < scene->mNumMaterials; i++)
	{
		diffuseTexture[i] = nullptr;
		specularTexture[i] = nullptr;

		aiMaterial* material= scene->mMaterials[i];

		//Getting material properties
		aiColor3D ambientReflectivity;
		aiColor3D diffuseReflectivity;
		aiColor3D specularReflectivity;
		float specularShine;

		material->Get(AI_MATKEY_COLOR_AMBIENT, ambientReflectivity);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseReflectivity);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specularReflectivity);
		material->Get(AI_MATKEY_SHININESS, specularShine);
		Material* nMaterial = new Material(program,ambientReflectivity.r, diffuseReflectivity.r, specularReflectivity.r, specularShine);
		materials.push_back(nMaterial);


		//getting diffuse texture
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString filePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);

			std::string relativePath = std::string("textures/") +
									   std::string(filePath.data).substr(std::string(filePath.data).rfind("\\")+1);

			diffuseTexture[i] = new Texture(this->program, relativePath.c_str(), 0);
		}
		


		//getting specular texture
		if (material->GetTextureCount(aiTextureType_SPECULAR))
		{
			aiString filePath;
			material->GetTexture(aiTextureType_SPECULAR, 0, &filePath);

			std::string relativePath = std::string("textures/") +
				std::string(filePath.data).substr(std::string(filePath.data).rfind("\\") + 1);

			specularTexture[i] = new Texture(this->program, relativePath.c_str(), 1);
		}
		
		//If missing texture attach default one for both diffuse and specular
		if(!diffuseTexture[i])
		{
			diffuseTexture[i] = new Texture(this->program, "textures/white.png",0);
		}
		if (!specularTexture[i])
		{
			specularTexture[i] = new Texture(this->program, "textures/black.png", 1);
		}
		
	}
}
