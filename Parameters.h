#include<stdio.h>

#define KOYO_MAX_TASK_COUNT	32


//参数中心进程的大结构体
typedef struct ParamCenter_
{
	int unix_socket;
	SystemParameters sys_params;
	TaskParameters	 tool_params;
} ParamCenter;


typedef struct ParamNode_
{
	unsigned int param_type;	//0 for system paramters; 1 for camera parameters; 2 for tool paramters; 3 for output parameters 
	unsigned int task_id;		//1~32 for 32 tasks; 
	unsigned int tool_type;		//1-4 for contour/circle/width/color
	unsigned int tool_id;		//1~0xFFFFFFFF for tools
	unsigned char payload[0];	//具体参数
} ParamNode;

//参数存Flash的头部
typedef struct ParamInFlash_
{
	unsigned int magic_head;	//0x4B4F594F
	unsigned int in_use;		// 1 - used; 0 - deleted;
	unsigned int version;		// 1~0xFFFFFFFF
	ParamNode parameter;		// parameters
}ParamInFlash;

//相机参数
typedef struct CameraParameters_
{
	unsigned int version;
	//TODO
} CameraParameters;

//输出参数
typedef struct OutputParameters_
{
	unsigned int version;
	//TODO
} OutputParameters;

//参数节点头部，payload位置存储具体参数，需根据具体工具类型进行解析
typedef struct ToolParamNode_
{
	struct ToolParamHead_ *tool_head; 
	unsigned int version;		//1~0xFFFFFFFF
	unsigned int tool_type;		//1-4 for contour/circle/width/color
	unsigned int tool_id;		//1~0xFFFFFFFF for tools
	unsigned char payload[0];	// for tool parameters
} ToolParamNode;

//任务参数结构体，通过参数节点指针来管理所有工具参数
typedef struct TaskParameters_
{
	CameraParameters camera_param;	//相机参数
	OutputParameters output_param;	//输出配置
	ToolParamNode *task_param_head[KOYO_MAX_TASK_COUNT];	//工具参数
	ToolParamNode *task_param_tail[KOYO_MAX_TASK_COUNT];	//工具参数
} TaskParameters;

//系统级参数，因为只有一份，可以把具体系统参数结构体组合成大结构体
typedef struct SystemParamters_
{
	unsigned int version;
	//TODO
} SystemParameters;