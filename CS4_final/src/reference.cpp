#include <vector>

using namespace std;

class ClassTest{
private:
	int a1;
public:
	ClassTest():a1(31){}
	~ClassTest(){}
	int usea1(int var1){
		cout<<"Memberfunction\n";
		cout<<var1<<endl;
		return 0;
	}

};

int nonmember(void*, int var1){
	cout<<"non-memberfunction\n";
	cout<<var1<<endl;
	return 0;
}

void forwarder(void* context,int var1){
	static_cast<ClassTest*>(context)->usea1(var1);
}

template<class D, class OP>
std::vector<D> Simplex(OP f,std::vector<D> init)

int main()
{

	return 0;
}