#include <sstream>
#include <ContainerTools.hpp>

template<typename TargetType>
void
ConfigLoader::Load(const std::string& section_, const std::string& fieldName_,  TargetType& loadVal_, typename enable_if<is_number<TargetType>::value, int>::type){
  loadVal_ = Converter<TargetType>()(fParser->top()(section_)[fieldName_]);
}


template<typename TargetType>
void
ConfigLoader::Load(const std::string& section_, const std::string& fieldName_, TargetType& loadVal_, typename enable_if<is_container<TargetType>::value, int>::type){
    typedef typename TargetType::value_type ContainedType;
    ConvertContainer(ContainerTools::Split(fParser->top()(section_)[fieldName_]), loadVal_, Converter<TargetType>());
}

template<typename TargetType>
TargetType
ConfigLoader::Converter<TargetType>::operator()(const std::string& s_) const{
    std::istringstream buffer(s_);
    TargetType val;
    buffer >> val;
    return val;
}

template<typename InContainer, typename OutContainer, typename ConverterSp>
void
ConfigLoader::ConvertContainer(const InContainer& incntr_, OutContainer& outcntr_, const ConverterSp& cnvtr_){
    for(typename InContainer::const_iterator it = incntr_.begin(); it != incntr_.end(); ++it){
        outcntr_.insert(outcntr_.end(), cnvtr_(*it));
    }
}
