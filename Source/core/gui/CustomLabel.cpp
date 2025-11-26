#include "CustomLabel.h"
#include "core/utils/StringUtility.h"

CustomLabel::CustomLabel(Size size) {

	_curId = 0;
	_font = "";
	_size = 20;
	_color = Color3B(255, 255, 255);

	_richText = ui::RichText::create();
	addChild(_richText);

	if (size.width != 0 && size.height != 0) {
		setTextContentSize(size);
	}
	else {
		setTextContentSize(Size(500, 200));
	}

 	_richText->ignoreContentAdaptWithSize(false);
}

CustomLabel::~CustomLabel() {

}

bool CustomLabel::init() {
	Layer::init();
	return true;
}

void CustomLabel::setIgnoreSize(bool val) {
	_richText->ignoreContentAdaptWithSize(val);
}

void CustomLabel::setTextContentSize(Size size) {
	_richText->setContentSize(size);
}

Size CustomLabel::getTextContentSize() {
	return _richText->getContentSize();
}

void CustomLabel::setDefaultFont(std::string font) {
	_font = font;
}

void CustomLabel::setDefaultSize(int size) {
	_size = size;
}

void CustomLabel::setDefaultColor(Color3B color) {
	_color = color;
}
//
//ui::RichText::Align CustomLabel::convertAlign(int align) {
//	return ui::RichText::Align::CENTER;
//}
//
//void CustomLabel::setDefaultAlignHorizontal(int val) {
//	_richText->setAlignmentHorizontal(convertAlign(val));
//}
//
//void CustomLabel::setDefaultAlignVertical(int val) {
//	_richText->setAlignmentVertical(convertAlign(val));
//}

void CustomLabel::appendText(std::string text, std::string font = "", int size = 20, Color3B color = Color3B(255,255,255), int opacity = 255, bool enableTouch = false) {
	if (size == 0) size = 20;
	if (opacity == 0) opacity = 255;

	ui::RichElementText *el = ui::RichElementText::create(
		getAutoId(),
		color,
		opacity,
		text,
		(!font.empty()) ? font : _font,
		size ? size : _size
	);

	_richText->pushBackElement(el);
	_richText->formatText();
}

void CustomLabel::clearText () {
	for (int i = 0; i < _curId; ++i) {
		_richText->removeElement(0);
	}
_curId = 0;
}

int CustomLabel::getAutoId () {
	return ++_curId;
}

void CustomLabel::setString (std::string text) {
	clearText();

	std::vector<std::string> splitArr;

	std::string tmpStr = text;
	while (true) {
		std::size_t index1 = tmpStr.find("<");
		if (index1 == 0) {
			index1 = tmpStr.find("<", 1);
		}
		if (index1 == std::string::npos) {
			splitArr.push_back(tmpStr);
			break;
		}

		splitArr.push_back(tmpStr.substr(0, index1));
		tmpStr = tmpStr.substr(index1);
	}

	std::vector<std::string> tmp1;
	for (int i = 0; i < (int)splitArr.size(); ++i) {
		std::size_t tmpIdx = splitArr[i].find(">");
		if (tmpIdx == std::string::npos) {
			tmp1.push_back(splitArr[i]);
			continue;
		}
		tmp1.push_back(splitArr[i].substr(0, tmpIdx + 1));
		if (tmpIdx + 1 < splitArr[i].size()) {
			tmp1.push_back(splitArr[i].substr(tmpIdx + 1));
		}
	}

	bool isCreateNewElement = false;
	int numTag = 0;
	CustomLabelObject obj;
	for (int i = 0; i < (int)tmp1.size(); ++i) {
		if (isCreateNewElement == false) {
			numTag = 0;
			memset(&obj, 0, sizeof(obj));
			isCreateNewElement = true;
		}

		if (tmp1[i].find("</") == std::string::npos && tmp1[i].find("<") == std::string::npos) {
			obj.text = tmp1[i];
			if (numTag == 0) {
				appendText(obj.text);
				isCreateNewElement = false;
			}
			continue;
		}
		if (tmp1[i].find("</") == std::string::npos && tmp1[i].find("<") >= 0) {
			// have override format
			numTag++;
			std::string oneTag = tmp1[i];
			std::string typeKey = oneTag.substr(1, oneTag.find(" ") - 1);
			std::string typeVal = oneTag.substr(oneTag.find_last_of(" ") + 1, oneTag.find(">") - oneTag.find_last_of(" ") - 1);
			if (typeKey.compare("text") == 0) {
				obj.text = typeVal;
			}
			else if (typeKey.compare("font") == 0) {
				obj.font = typeVal;
			}
			else if (typeKey.compare("size") == 0) {
				obj.size = std::atoi(typeVal.c_str());
			}
			else if (typeKey.compare("opacity") == 0) {
				obj.opacity = std::atoi(typeVal.c_str());
			}
			else if (typeKey.compare("color") == 0) {
				obj.color = parseColor(typeVal);
			}
			continue;
		}
		if (tmp1[i].find("</") >= 0) {
			numTag--;
			if (numTag <= 0) {
				appendText(obj.text, obj.font, obj.size, obj.color, obj.opacity,true);
				isCreateNewElement = false;
			}
		}
	}
}

Color3B CustomLabel::parseColor(std::string text) {
	std::vector<std::string> ar = StringUtility::splitString(text, ",");
	
	Color3B color;
	if (ar.size() == 3) {
		color.r = (GLubyte)std::atoi(ar[0].c_str());
		color.g = (GLubyte)std::atoi(ar[1].c_str());
		color.b = (GLubyte)std::atoi(ar[2].c_str());
	}
	return color;
}
