// TimeSeriesNetworkSimulator.cpp : iƒŠƒ“ƒNEŠÔjƒZƒbƒg‚Å‰e‹¿‚ğ—^‚¦‚é‚©‚Ç‚¤‚©‚ÌƒmƒCƒY‚ğ‚¢‚ê‚éB‚P‚O“`‚X‚O“
//

#include "stdafx.h"
#include <direct.h>


int _tmain(int argc, _TCHAR* argv[])
{
	string dataDir("B:/workspace-c/data/time-series-network/input/exp15/");
	string outputDir("B:/transfer-entropy/artificial_experiment/ver1.0/TE_ver1_exp_ver15/");

	//user topci
	map<int, string> userTopicMap = readCsv(dataDir + "user-topic.csv");
	int userNum = userTopicMap.size();

	// network
	map<int, string> networkMap = readCsv(dataDir + "network.csv");

	// influencer
	string influencer = readText(dataDir + "influencer.txt");
	int tlen = influencer.length();

	// noise roop
	for (int noi = 1; noi <= 9; noi++) {
		int noiseNum = noi * 10;
		for (int roopCount = 1; roopCount < 6; roopCount++) {
			// influence
			int influence[10][10] = {
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
				{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

			// noise
			for (int i = 0; i < noiseNum; i++) {
				int randomNum = GetRandom(0, 99);
				influence[randomNum / 10][randomNum % 10] = 0;
			}

			// result matrix init
			string ** result = new string*[userNum];
			for (int i = 0; i < userNum; i++) {
				result[i] = new string[tlen];
			}

			// result <- influencer
			for (int i = 0; i < tlen; i++){
				result[0][i] = influencer[i];
			}

			// result <- 0
			for (int i = 1; i < userNum; i++) {
				for (int j = 0; j < tlen; j++) {
					result[i][j] = "0";
				}
			}

			// init
			for (int i = 0; i < userNum; i++) {
				for (int j = 0; j < tlen; j++) {
					cout << result[i][j];
				}
				cout << endl;
			}


			// simulate
			for (int i = 1; i < tlen; i++) {
				cout << "time: " << i << endl;
				for (int j = 1; j < userNum; j++) {
					string link = networkMap[j];
					string mytopic = userTopicMap[j];
					int influenceFlag = 0;
					if (i == 5 && j == 1) {
						cout << "stop" << endl;
					}
					for (int l = 0; l < link.size(); l++) {
						set<int> influence_topics;
						// link”»’è
						if (link[l] == '1' && influence[l][i - 1]) {
							// topic”»’è
							string partnerTopic = userTopicMap[l];
							for (int m = 0; m < mytopic.size(); m++) {
								for (int n = 0; n < partnerTopic.size(); n++) {
									if (mytopic[m] == partnerTopic[n]) {
										if (influence_topics.find(chatToInt(mytopic[m])) == influence_topics.end()) {
											influence_topics.insert(chatToInt(mytopic[m]));
										}
									}
								}
							}
							// ‰e‹¿’l”»’è
							cout << "influence_topics" << endl;
							std::set< int >::iterator pos = influence_topics.begin();//æ“ª‚Ì—v‘f‚ğæ“¾‚·‚é
							while (pos != influence_topics.end()){//ÅŒã‚Ì—v‘f‚É’B‚·‚é‚Ü‚Åƒ‹[ƒv
								printf("%d\n", *pos);//’l‚ğ•\¦
								pos++;//ˆê‚Âi‚ß‚é
							}
							cout << "result[l][i-1]" << stringToInt(result[l][i - 1]) << endl;
							if (influence_topics.count(stringToInt(result[l][i - 1])) > 0) {
								result[j][i] = result[l][i - 1];
								influenceFlag = 1;
								break;
							}
						}
					}
					// ‰e‹¿‚È‚µ
					if (influenceFlag == 0) {
						cout << result[j][i - 1] << endl;
						result[j][i] = result[j][i - 1];
					}
				}

				for (int i = 0; i < userNum; i++) {
					for (int j = 0; j < tlen; j++) {
						cout << result[i][j];
					}
					cout << endl;
				}
			}

			// output
			string outputStr("");
			cout << "output" << endl;
			for (int i = 0; i < userNum; i++) {
				cout << result[i][0];
				outputStr = outputStr + result[i][0];
				for (int j = 1; j < tlen; j++) {
					cout << result[i][j];
					outputStr = outputStr + "," + result[i][j];
				}
				outputStr = outputStr + "\n";
				cout << endl;
			}

			// make dir
			string dir(outputDir + intToString(noiseNum) + "/");
			int len = dir.length();
			char* dirC = new char[len + 1];
			memcpy(dirC, dir.c_str(), len + 1);
			_mkdir(dirC);
			string dir2(outputDir + intToString(noiseNum) + "/" + intToString(roopCount) + "/");
			int len2 = dir2.length();
			char* dirC2 = new char[len2 + 1];
			memcpy(dirC2, dir2.c_str(), len2 + 1);
			_mkdir(dirC2);


			// output time series file open
			ofstream result_file;
			result_file.open(dir2 + "exp_ver15" + intToString(noi) + intToString(roopCount) + "_network-time-series.csv", ios::out);
			result_file << outputStr;
			result_file.close();

			// output noise link
			string noiseStr("");
			cout << "output" << endl;
			for (int a = 0; a < 10; a++) {
				noiseStr = noiseStr + intToString(influence[a][0]);
				for (int b = 1; b < 10; b++) {
					noiseStr = noiseStr + "," + intToString(influence[a][b]);
				}
				noiseStr = noiseStr + "\n";
				cout << endl;
			}

			ofstream noise_file;
			noise_file.open(dir2 + "noise_ver15" + intToString(noi) + intToString(roopCount) + "_network-time-series.txt", ios::out);
			noise_file << noiseStr;
			noise_file.close();


			// result matrix close
			for (int i = 0; i < userNum; i++) {
				delete[] result[i];
			}
			delete[] result;

		}
	}

	return 0;
}


string readText(string path)
{
	ifstream ifs(path);

	if (ifs.fail()){
		// error
		cerr << "failed." << endl;
		exit(0);
	}

	string result;
	ifs >> result;

	return result;
}


map<int, string> readCsv(string path)
{
	ifstream ifs(path);
	map<int, string> result;

	if (ifs.fail()){
		// error
		cerr << "failed." << endl;
		exit(0);
	}

	string line;
	string lineSum;
	int p;
	int index = 0;
	while (getline(ifs, line)){
		lineSum = "";
		while ((p = line.find(",")) != line.npos){
			lineSum = lineSum + line.substr(0, p);
			line = line.substr(p + 1);
		}
		lineSum = lineSum + line.substr(0, p);
		result.insert(map<int, string>::value_type(index, lineSum));
		index = index + 1;
	}

	return result;
}

string intToString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}

int stringToInt(string s)
{
	int v;
	istringstream sin(s);
	sin >> v;
	return v;
}

int chatToInt(char c)
{
	return (int)(c - '0');
}

int GetRandom(int min, int max)
{
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}