##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CPU
ConfigurationName      :=Debug
WorkspacePath          := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming"
ProjectPath            := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ilya
Date                   :=08/12/16
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
ObjectsFileList        :="CPU.txt"
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) $(IntermediateDirectory)/Ass_Disass.cpp$(ObjectSuffix) 



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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix): Stack.cpp $(IntermediateDirectory)/Stack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU/Stack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Stack.cpp$(DependSuffix): Stack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Stack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Stack.cpp$(DependSuffix) -MM "Stack.cpp"

$(IntermediateDirectory)/Stack.cpp$(PreprocessSuffix): Stack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Stack.cpp$(PreprocessSuffix) "Stack.cpp"

$(IntermediateDirectory)/Ass_Disass.cpp$(ObjectSuffix): Ass_Disass.cpp $(IntermediateDirectory)/Ass_Disass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/CPU/Ass_Disass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Ass_Disass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Ass_Disass.cpp$(DependSuffix): Ass_Disass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Ass_Disass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Ass_Disass.cpp$(DependSuffix) -MM "Ass_Disass.cpp"

$(IntermediateDirectory)/Ass_Disass.cpp$(PreprocessSuffix): Ass_Disass.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Ass_Disass.cpp$(PreprocessSuffix) "Ass_Disass.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


