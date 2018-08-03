// 컴파일러 개발
// 제품별(sun, hp)
// Scanner, Parset, Generator, Optimizer
// 클래스 구조, sun ? hp 동일한작업


int g_iType = 0; // sun
#define SUN 0
#define HP 1

void SunWork() 
{
	//Scanner();
	//Parset();
	//Generator(); 
	//Optimizer();
}
void HpWork() 
{

}
class Scanner {};
class Parsor {};
class Generator {};
class Optimizer {};

class CompilerFactory
{
public:
	virtual Scanner* CreateScanner() = 0;
	virtual Parsor* CreateParsor() = 0;
	virtual Generator* CreateGenerator() = 0;
	virtual Optimizer* CreateOptimizer() = 0;
};
class HPCompilerFactory : public CompilerFactory
{
public:
	Scanner* CreateScanner() { return new HPScanner; }
	Parsor* CreateParsor() { return new HPParsor; }
	Generator* CreateGenerator() { return new HPGenerator; }
	Optimizer* CreateOptimizer() { return new HPOptimizer; }
};
class SunCompilerFactory : public CompilerFactory
{
public:
	Scanner* CreateScanner() { return new SunScanner; }
	Parsor* CreateParsor() { return new SunParsor; }
	Generator* CreateGenerator() { return new SunGenerator; }
	Optimizer* CreateOptimizer() { return new SunOptimizer; }
};

class HPScanner : public Scanner {};
class HPParsor : public Parsor {};
class HPGenerator : public Generator{};
class HPOptimizer : public Optimizer {};

class SunScanner : public Scanner {};
class SunParsor : public Parsor {};
class SunGenerator : public Generator {};
class SunOptimizer : public Optimizer {};

class OsScanner : public Scanner {}; //새로운거 추가
class OsParsor : public Parsor {};
class OsGenerator : public Generator {};
class OsOptimizer : public Optimizer {};

void ScanParse(void)
{
	if (g_iType == SUN)
	{
		SunScanner scan;
		SunParsor parsor;
	}
	else if(g_iType == HP)
	{
		HPScanner scan;
		HPParsor parsor;
	}
	else
	{
		OsScanner scan;
		OsParsor parsor;
	}
}
void CodeGenOptimize(void)
{
	if (g_iType == SUN)
	{
		SunGenerator generator;
		SunOptimizer optimizer;
	}
	else if (g_iType == 1)
	{
		HPGenerator generator;
		HPOptimizer optimizer;
	}
	else
	{
		OsGenerator generator;
		OsOptimizer optimizer;
	}
}

int main(void)
{
	g_iType = SUN;
	CompilerFactory * g_pFactory = nullptr;
	if (g_iType == HP)
	{
		g_pFactory = new HPCompilerFactory;
	}
	else
	{
		g_pFactory = new SunCompilerFactory;
	}
	Scanner * pScanner = g_pFactory->CreateScanner();
	Parsor * pParsor = g_pFactory->CreateParsor();
	Generator * pGenerator = g_pFactory->CreateGenerator();
	Optimizer * pOptimizer = g_pFactory->CreateOptimizer();

	return 0;
}