#define PLAIN "text/plain"
#define HTML "text/html"
#define IMAGE "image/png"

vector<string> split(string str)
{
	string buf;
	str.erase(remove(str.begin(), str.end(), '\n'), str.cend());
	stringstream ss(str);

	vector<string> splitted;
	while (getline(ss, buf, ' '))
		splitted.push_back(buf);

	return splitted;
}

bool pathExists(string path)
{
	ifstream s;
	path = "./" + path;
	s.open("./" + path);
	if (s)
		return true;

	return false;
}

string contentType(string path)
{

	if (path.find(".html") != std::string::npos)
		return HTML;

	if (path.find(".png") != std::string::npos)
		return IMAGE;

	return PLAIN;
}