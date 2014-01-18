// NetworkTimeSeriesSimulator.cpp : ネットワークを仮定し、情報が伝播する過程をシミュレートするtest
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//user topci
	map<int, string> userTopicMap = readCsv("B:/workspace-c/data/time-series-network/input/exp11/user-topic.csv");
	int userNum = userTopicMap.size();

	// network
	map<int, string> networkMap = readCsv("B:/workspace-c/data/time-series-network/input/exp11/network.csv");

	// influencer
	string influencer = readText("B:/workspace-c/data/time-series-network/input/exp11/influencer.txt");
	int tlen = influencer.length();

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
				// link判定
				if (link[l] == '1') {
					// topic判定
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
					// 影響値判定
					cout << "influence_topics" << endl;
					std::set< int >::iterator pos = influence_topics.begin();//先頭の要素を取得する
					while (pos != influence_topics.end()){//最後の要素に達するまでループ
						printf("%d\n", *pos);//値を表示
						pos++;//一つ進める
					}
					cout << "result[l][i-1]" << stringToInt(result[l][i - 1]) << endl;
					if (influence_topics.count(stringToInt(result[l][i - 1])) > 0) {
						result[j][i] = result[l][i - 1];
						influenceFlag = 1;
						break;
					}
				}
			}
			// 影響なし
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
	cout << "output" << endl;
	for (int i = 0; i < userNum; i++) {
		for (int j = 0; j < tlen; j++) {
			cout << result[i][j];
		}
		cout << endl;
	}


	// result matrix close
	for (int i = 0; i < userNum; i++) {
		delete[] result[i];
	}
	delete[] result;


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