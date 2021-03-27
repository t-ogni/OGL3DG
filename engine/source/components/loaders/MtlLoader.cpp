#include "MtlLoader.h"

std::map<std::string, SurfaceStruct *> MtlLoader::loadMtlFromFile(const char *path) {
    auto surfaces = std::map<std::string, SurfaceStruct *>();
    std::string currentMtl;
    std::ifstream mtlFile(path);
    if (!mtlFile) {
        Log->warning("Material file in %s cannot be opened", path);
        return surfaces;
    }
    Log->info("Material file in %s was loaded successfully", path);
    std::string fileLine;
    while (mtlFile) {
        getline(mtlFile, fileLine);
        std::istringstream lineStream(fileLine);
        std::string oper;
        lineStream >> oper;
        if (oper == "newmtl") {
            lineStream >> currentMtl;
            surfaces[currentMtl] = new SurfaceStruct();
        } else if (oper == "Ka") {
            glm::vec3 Ka;
            lineStream >> Ka.x >> Ka.y >> Ka.z;
            surfaces[currentMtl]->ambient = Ka;
        } else if (oper == "Kd") {
            glm::vec3 Kd;
            lineStream >> Kd.x >> Kd.y >> Kd.z;
            surfaces[currentMtl]->diffuse = Kd;
        } else if (oper == "Ks") {
            glm::vec3 Ks;
            lineStream >> Ks.x >> Ks.y >> Ks.z;
            surfaces[currentMtl]->specular = Ks;
        } else if (oper == "d") {
            float d;
            lineStream >> d;
            surfaces[currentMtl]->alfa = d;
        } else if (oper == "Ns") {
            float Ns;
            lineStream >> Ns;
            surfaces[currentMtl]->shine = Ns;
        } else if (oper == "illum") {
            int n;
            lineStream >> n;
            surfaces[currentMtl]->illumination = n;
        }
    }
    return surfaces;
}
