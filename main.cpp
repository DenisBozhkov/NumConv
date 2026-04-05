#include "converter.h"
using namespace std;
int main(int argc, char** argv) 
{
	MessageHandler handler;
	std::vector<std::string> args;
	for(int i=1;i<argc;i++)
		args.push_back(std::string(argv[i]));
	Options options=Options::get_options(args,handler);
	try
	{
		Converter converter(options);
		converter.read();
		converter.convert();
		if(!options.has_output_file())
			cout<<endl;
		if(!options.has_output_file()||handler.is_handled())
			cout<<"--------------------------------\n";
		options.print_success_message();
	}
	catch(exception e)
	{
		handler.error(e.what());
	}
	return 0;
}