##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=compiler
ConfigurationName      :=Debug
WorkspacePath          := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming"
ProjectPath            := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/compiler"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ilya
Date                   :=11/12/16
CodeLitePath           :="/home/ilya/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
ObjectsFileList        :="compiler.txt"
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/Tree.c$(ObjectSuffix) $(IntermediateDirectory)/Tokens.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/compiler/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/Tree.c$(ObjectSuffix): Tree.c $(IntermediateDirectory)/Tree.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/compiler/Tree.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tree.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tree.c$(DependSuffix): Tree.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tree.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Tree.c$(DependSuffix) -MM "Tree.c"

$(IntermediateDirectory)/Tree.c$(PreprocessSuffix): Tree.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tree.c$(PreprocessSuffix) "Tree.c"

$(IntermediateDirectory)/Tokens.c$(ObjectSuffix): Tokens.c $(IntermediateDirectory)/Tokens.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/compiler/Tokens.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tokens.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Tokens.c$(DependSuffix): Tokens.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Tokens.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Tokens.c$(DependSuffix) -MM "Tokens.c"

$(IntermediateDirectory)/Tokens.c$(PreprocessSuffix): Tokens.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Tokens.c$(PreprocessSuffix) "Tokens.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


