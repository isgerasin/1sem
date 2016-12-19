##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CPU1
ConfigurationName      :=Debug
WorkspacePath          := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming"
ProjectPath            := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU1"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ilya
Date                   :=19/12/16
CodeLitePath           :="/home/ilya/.codelite"
LinkerName             :=/usr/bin/x86_64-linux-gnu-g++
SharedObjectLinkerName :=/usr/bin/x86_64-linux-gnu-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="CPU1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/x86_64-linux-gnu-ar rcu
CXX      := /usr/bin/x86_64-linux-gnu-g++
CC       := /usr/bin/x86_64-linux-gnu-gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/x86_64-linux-gnu-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) $(IntermediateDirectory)/Assembler.cpp$(ObjectSuffix) $(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU1/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix): Stack.cpp $(IntermediateDirectory)/Stack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU1/Stack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stack.cpp$(DependSuffix): Stack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stack.cpp$(DependSuffix) -MM "Stack.cpp"

$(IntermediateDirectory)/Stack.cpp$(PreprocessSuffix): Stack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stack.cpp$(PreprocessSuffix) "Stack.cpp"

$(IntermediateDirectory)/Assembler.cpp$(ObjectSuffix): Assembler.cpp $(IntermediateDirectory)/Assembler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU1/Assembler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Assembler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Assembler.cpp$(DependSuffix): Assembler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Assembler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Assembler.cpp$(DependSuffix) -MM "Assembler.cpp"

$(IntermediateDirectory)/Assembler.cpp$(PreprocessSuffix): Assembler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Assembler.cpp$(PreprocessSuffix) "Assembler.cpp"

$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix): CPU.cpp $(IntermediateDirectory)/CPU.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU1/CPU.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPU.cpp$(DependSuffix): CPU.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CPU.cpp$(DependSuffix) -MM "CPU.cpp"

$(IntermediateDirectory)/CPU.cpp$(PreprocessSuffix): CPU.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPU.cpp$(PreprocessSuffix) "CPU.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


