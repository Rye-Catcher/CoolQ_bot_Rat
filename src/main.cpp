#include <cqcppsdk/cqcppsdk.h>
#include <iostream>
#include <set>
#include <algorithm>
#include <ctime>
#include <sstream>
#include "getmusic.h"
#include "acg_sentences.h"
#include "hitokoto.h"
#include "greeting.h"
#include "runcode.h"
#include "deadline.h"
#include "ChineseToUTF8.h"


/*写得比较乱见谅*/

/*第一个头文件<cqcppsdk/cqcppsdk.h>必须放在最上面 https://github.com/cqmoe/cqcppsdk/issues/1*/
/*自己写的头文件中，最好把变量及函数放在 class 或 namespace 里，不然容易编译错误（玄学）*/

using namespace cq;
using namespace std;
using Message = cq::message::Message;
using MessageSegment = cq::message::MessageSegment;


/*--------------------------------------------------------------*/
/*请设置你要保存运行代码(实现 #runcode )的绝对路径 (路径名称中请使用\\)*/
/*PLease set the path to save the code (remember to use \\)*/
const string code_src_path="G:\\Github Repositories\\CoolQ_C++\\src\\";

/*请设置成 main.cpp 所在的绝对路径 (路径名称中请使用\\)*/
/*PLease set the path of this "main.cpp" (remember to use \\)*/
const string src_path="G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\";

CQ_INIT {
    on_enable([] { logging::info("启用", "插件已启用"); });

    on_private_message([](const PrivateMessageEvent &event) { //私聊模块
        try {
            auto usr_text=event.message; //接受的用户信息 (string类型)
            char _text_id[1000];
            sscanf(usr_text.c_str(), "%s", _text_id);
            string text_id(_text_id);

            if(text_id == "#runcode_cpp"){
 
                string text_code = usr_text.substr(text_id.length()+1);
                string output_text = RunCpp::_main(code_src_path, text_code);
                
                send_message(event.target, output_text);  //发送信息 (string类型)
            }
            else if(text_id == "#runcode_c"){
                string text_code = usr_text.substr(text_id.length()+1);
                string output_text = RunC::_main(code_src_path, text_code);
                
                send_message(event.target, output_text);    
            }
            
        } catch (ApiError &err) {
            logging::warning("私聊", "私聊消息回复失败, 错误码: " + to_string(err.code));
        }
    });
	
    on_private_message([](const PrivateMessageEvent &event) { 
        try {
                if(event.message == "#一言" || event.message == "#hitokoto"){
                    char buf[1000];
                    string output;
                    FILE *fp=NULL;

                    GetHitokoto::httpget(src_path);
                    string command = src_path + "hitokoto.txt";
                    fp = fopen(command.c_str(), "r");
                    //fp = fopen("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "r");
				    fgets(buf, 1000, fp);
                    fclose(fp);

				    string output_text(buf);
                
				    send_message(event.target, output_text);	
                }
                
        } catch (ApiError &err) {
            logging::warning("私聊", "私聊消息回复失败, 错误码: " + to_string(err.code));
        }
    });

    on_private_message([](const PrivateMessageEvent &event) { 
        try {
                auto usr_text=event.message;
                char _text_id[1000];

                sscanf(usr_text.c_str(), "%s", _text_id);
                string text_id(_text_id);

                if(text_id == "#音乐" ||text_id == "#music" ){

                    char buf[1000];
                    string output;
                    FILE *fp=NULL;

                    string text_topic = usr_text.substr(text_id.length()+1);

                    if(text_topic.empty()) send_message(event.target, "请在后面输入名字哦");

                    else{

                        GetMusic::getmusic(src_path, text_topic);
                
                        string command = src_path + "getmusic.txt";
                        fp = fopen(command.c_str(), "r");
                        //fp = fopen("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "r");
                        memset(buf,0,sizeof(buf));
				        fgets(buf, 1000, fp);
                        fclose(fp);

				        string output_text(buf);
                    
                        if(output_text.empty()) send_message(event.target, "似乎出了点小问题...");

                        else send_message(event.target, output_text);	
                    }
				
                }
                
        } catch (ApiError &err) {
            logging::warning("私聊", "私聊消息回复失败, 错误码: " + to_string(err.code));
        }
    });

	on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169, 870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
			if(event.message == "#帮助"||event.message== "#help"){
                string output_text="I am a Bot and my name is Rat\n\n";
                output_text+="\"#文章生成 something\"：生成一篇以\"something\"为主题的文章\n";
                output_text+="\"#runcode_c\"：运行C语言代码并输出结果（支持私聊）\n";
                output_text+="\"#runcode_cpp\"：运行C++语言代码并输出结果（支持私聊）\n";
                output_text+="\"#一言\": 获取一句来自 https://hitokoto.cn/ 的话（支持私聊）\n";
                output_text+="\"#音乐 名字\"：获取音乐的播放与下载链接,音乐名建议小写，部分特殊字符暂不支持，可加入作者或是专辑等相关信息增加辨识度（支持私聊）\n";
                output_text+="\"#二次元\"：增加你的二次元浓度\n";
                output_text+="\"#问好\"：收获一句温馨的问候\n";
                output_text+="\"#体温\": to declare your temperature\n";
                output_text+="\"#电竞 游戏名\"：获得相关游戏的赛事咨询\n";
                output_text+="\"#新冠病毒\"：获得新冠病毒相关资讯\n";
                output_text+="\"#deadline\"：获取接下来的 deadline\n";
                output_text+="\nGithub: https://github.com/Rye-Catcher/CoolQ_bot_Rat\n";
				send_message(event.target, output_text);	
			}
		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
            auto usr_text=event.message;
            char _text_id[1000];
            sscanf(usr_text.c_str(), "%s", _text_id);
            string text_id(_text_id);

            if(text_id == "#runcode_cpp"){
 
                string text_code = usr_text.substr(text_id.length()+1);
                string output_text = RunCpp::_main(code_src_path, text_code);
                
                send_message(event.target, output_text);    
            }
            else if(text_id == "#runcode_c"){
                string text_code = usr_text.substr(text_id.length()+1);
                string output_text = RunC::_main(code_src_path, text_code);
                
                send_message(event.target, output_text);    
            }
         
		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
            auto usr_text=event.message;
            char _text_id[1000], _text_topic[1000];

            sscanf(usr_text.c_str(), "%s %s", _text_id, _text_topic);
            string text_id(_text_id);

			if(text_id=="#文章生成")
            {
                srand(time(0));
                string text_topic(_text_topic);

                if(text_topic.empty()) send_message(event.target, "请在后面输入主题哦");
                else {

                    auto art_url="https://suulnnka.github.io/BullshitGenerator/index.html?主题="+text_topic+"&随机种子="+to_string(rand()*rand()%19260817+1);
                
                    //CN2Utf8( art_url.c_str(), _output_url);
                    //string output_url(_output_url);
                    send_message(event.target, art_url);

                }
            }

            else  if(text_id == "#音乐" ||text_id == "#music" ){

                char buf[1000];
                string output;
                FILE *fp=NULL;

                string text_topic = usr_text.substr(text_id.length()+1);

                if(text_topic.empty()) send_message(event.target, "请在后面输入名字哦");

                else{

                    GetMusic::getmusic(src_path, text_topic);
                
                    string command = src_path + "getmusic.txt";
                    fp = fopen(command.c_str(), "r");
                    //fp = fopen("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "r");
                    memset(buf,0,sizeof(buf));
				    fgets(buf, 1000, fp);
                    fclose(fp);

				    string output_text(buf);
                    
                    if(output_text.empty()) send_message(event.target, "似乎出了点小问题...");

                    else send_message(event.target, output_text);	
                }
				
            }

            else if(text_id=="#电竞"){
                    
                string text_topic(_text_topic);
                string output_text;

                if(text_topic.empty()) output_text="请输入游戏名哦";

                else if(text_topic=="CSGO"||text_topic=="CS:GO"){
                    output_text="https://www.hltv.org/";
                }
                else if(text_topic=="王者荣耀"||text_topic=="王者"){
                    output_text="https://pvp.qq.com/match/kpl/index.shtml";
                }
                else if(text_topic=="彩虹六号"||text_topic=="彩虹6号"||text_topic=="彩六"){
                    output_text="https://pro.eslgaming.com/r6/proleague/";
                }
                else if(text_topic=="LOL" || text_topic=="lol" || text_topic=="英雄联盟"){
                    output_text="https://lpl.qq.com/";
                }
                else if(text_topic=="吃鸡" || text_topic=="绝地求生" || text_topic=="PUBG"){
                    output_text="https://cn.pubgesports.com/";
                }
                else {
                    output_text="Oops...暂时没有收录这个游戏";
                }

                send_message(event.target, output_text);
            }
       
		} catch (ApiError &){}
		
		event.block();
	});
    
    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
			if(event.message == "#Deadline"||event.message == "#deadline"){
				send_message(event.target, Deadline::deadline);	
			}
		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{

			if(event.message == "#一言" ||event.message== "#hitokoto" ){
                
                char buf[1000];
                string output;
                FILE *fp=NULL;

                GetHitokoto::httpget(src_path);
                
                string command = src_path + "hitokoto.txt";
                fp = fopen(command.c_str(), "r");
                //fp = fopen("G:\\Github Repositories\\CoolQ_C++\\bot Rat\\src\\hitokoto.txt", "r");
				fgets(buf, 1000, fp);
                fclose(fp);

				string output_text(buf);
                
				send_message(event.target, output_text);	
			}


		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
            srand(time(NULL));
			if(event.message == "#体温"||event.message=="#temperature"){
				send_message(event.target, "https://myaces.nus.edu.sg/htd/htd" );	
			}
		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
            srand(time(NULL));
			if(event.message == "#问好"){
				send_message(event.target, Greeting::ZuAn[rand()*rand()%(Greeting::ZuAn_size)]);	
			}
		} catch (ApiError &){}
		
		event.block();
	});

    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
            srand(time(NULL));
			if(event.message == "#二次元"){
				send_message(event.target, ACG_Sentences::acg_sentences[rand()*rand()%(ACG_Sentences::size)]);	
			}
		} catch (ApiError &){}
		
		event.block();
	});

    
    on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169,870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return; 
		
		try{
			auto usr_text=event.message;
            char _text_id[1000], _text_topic[1000];
            sscanf(usr_text.c_str(), "%s %s", _text_id, _text_topic);
            string text_id(_text_id);

            if(text_id=="#新冠病毒"||text_id=="#CoronaVirus"||text_id=="#新冠肺炎"){
                string text_topic(_text_topic);
                string output_text;

                if(text_topic=="新加坡"||text_topic=="Singapore"){
                    output_text="https://www.moh.gov.sg/covid-19 \n https://www.gov.sg/article/covid-19-cases-in-singapore";
                }
                else {
                    output_text="https://ncov.dxy.cn/ncovh5/view/pneumonia";
                }
                send_message(event.target, output_text);
            }

		} catch (ApiError &){}
		
		event.block();
	});


	on_group_message([](const GroupMessageEvent &event) {
		static const set<int64_t> ENABLED_GROUPS = {579911169, 870704381};
		if (ENABLED_GROUPS.count(event.group_id) == 0) return;
		
		try{
			if(event.message == "#谷歌"){
				send_message(event.target, MessageSegment::share("https://www.google.com/", "Google", "", ""));
			}
		} catch (ApiError &){}
		
		event.block();
	});
	
}

