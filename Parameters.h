#include<stdio.h>

#define KOYO_MAX_TASK_COUNT	32


//�������Ľ��̵Ĵ�ṹ��
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
	unsigned char payload[0];	//�������
} ParamNode;

//������Flash��ͷ��
typedef struct ParamInFlash_
{
	unsigned int magic_head;	//0x4B4F594F
	unsigned int in_use;		// 1 - used; 0 - deleted;
	unsigned int version;		// 1~0xFFFFFFFF
	ParamNode parameter;		// parameters
}ParamInFlash;

//�������
typedef struct CameraParameters_
{
	unsigned int version;
	//TODO
} CameraParameters;

//�������
typedef struct OutputParameters_
{
	unsigned int version;
	//TODO
} OutputParameters;

//�����ڵ�ͷ����payloadλ�ô洢�������������ݾ��幤�����ͽ��н���
typedef struct ToolParamNode_
{
	struct ToolParamHead_ *tool_head; 
	unsigned int version;		//1~0xFFFFFFFF
	unsigned int tool_type;		//1-4 for contour/circle/width/color
	unsigned int tool_id;		//1~0xFFFFFFFF for tools
	unsigned char payload[0];	// for tool parameters
} ToolParamNode;

//��������ṹ�壬ͨ�������ڵ�ָ�����������й��߲���
typedef struct TaskParameters_
{
	CameraParameters camera_param;	//�������
	OutputParameters output_param;	//�������
	ToolParamNode *task_param_head[KOYO_MAX_TASK_COUNT];	//���߲���
	ToolParamNode *task_param_tail[KOYO_MAX_TASK_COUNT];	//���߲���
} TaskParameters;

//ϵͳ����������Ϊֻ��һ�ݣ����԰Ѿ���ϵͳ�����ṹ����ϳɴ�ṹ��
typedef struct SystemParamters_
{
	unsigned int version;
	//TODO
} SystemParameters;