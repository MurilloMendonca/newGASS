#include "newGASS-base/newGASS.hpp"
#include <iostream>
#include <string>
using namespace std;
namespace compatGASS{
    void run(string setupFilePath, string templatesFilePath,
             string substitutionsFilePath, string proteinFilePath,
             string outputFilePath, string templateFolderPath, float centroide[3]){
                Repositorio repositorio;
                vector<site> templates;
                GASS::readConfigFile(setupFilePath);
                GASS::readSetupTemplateFile(templatesFilePath, templates);
                for(site& s : templates)
                    GASS::readTemplateFile(templateFolderPath+s.pdbId, s);
                repositorio.readRepository(proteinFilePath);
                GASS::readSubstitutuionMatrix(substitutionsFilePath, templates);
                GASS::run(std::ref(templates), std::ref(repositorio),outputFilePath);
                // for(site& s : templates){
                //     std::set<Individuo> results;
                //     GASS::runOneToOne(&s, &repositorio, &results);
                // }

             }
}
int main(int argc, char** argv){
    float centroide[3] = {0,0,0};
    if (argc != 6 && argc != 3)
	{
		throw "Error! Parameters missing!\nParameter:" + argc;
	}
	else if (argc == 6)
	{
        string coord;
		for (int i = 0; i < 3; i++)
		{
			coord=argv[i + 3];
			centroide[i] = stof(coord);
		}
	}
    string proteinFolderPath = argv[1];
    if (proteinFolderPath.back() != '/') proteinFolderPath += '/';
    string outputFilePath = proteinFolderPath+"NewActiveSitesFound.txt";
    string proteinFilePath = proteinFolderPath+"protein.dat";

    string templateFolderPath = argv[2];
    if (templateFolderPath.back() != '/') templateFolderPath += '/';
    string setupFilePath = templateFolderPath+"GA_Conf.txt";
    string templatesFilePath = templateFolderPath+"Templates.txt";
    string substitutionsFilePath = templateFolderPath+"SubstitutionMatrix.txt";

    compatGASS::run(setupFilePath, templatesFilePath, substitutionsFilePath, proteinFilePath, outputFilePath, templateFolderPath, centroide);
    return 0;
}