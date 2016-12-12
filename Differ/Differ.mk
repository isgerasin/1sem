##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Differ
ConfigurationName      :=Debug
WorkspacePath          := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming"
ProjectPath            := "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/Differ"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ilya
Date                   :=08/12/16
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
ObjectsFileList        :="Differ.txt"
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
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/Diff_Tree.c$(ObjectSuffix) $(IntermediateDirectory)/Diff.c$(ObjectSuffix) 



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
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/Differ/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/Diff_Tree.c$(ObjectSuffix): Diff_Tree.c $(IntermediateDirectory)/Diff_Tree.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/Differ/Diff_Tree.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Diff_Tree.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Diff_Tree.c$(DependSuffix): Diff_Tree.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Diff_Tree.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Diff_Tree.c$(DependSuffix) -MM "Diff_Tree.c"

$(IntermediateDirectory)/Diff_Tree.c$(PreprocessSuffix): Diff_Tree.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Diff_Tree.c$(PreprocessSuffix) "Diff_Tree.c"

$(IntermediateDirectory)/Diff.c$(ObjectSuffix): Diff.c $(IntermediateDirectory)/Diff.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/ilya/48AC7766EB621CC7/Programms_Codelite/Industrial Programming/Differ/Diff.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Diff.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Diff.c$(DependSuffix): Diff.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Diff.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Diff.c$(DependSuffix) -MM "Diff.c"

$(IntermediateDirectory)/Diff.c$(PreprocessSuffix): Diff.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Diff.c$(PreprocessSuffix) "Diff.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


