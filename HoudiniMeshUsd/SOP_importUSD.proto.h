/* Automagically Generated by generate_proto.py
 * Do not Edit
 */
#pragma once

#include <SOP/SOP_NodeVerb.h>
#include <SOP/SOP_GraphProxy.h>

#include <OP/OP_Utils.h>
#include <PRM/PRM_Parm.h>
#include <UT/UT_IStream.h>
#include <UT/UT_NTStreamUtil.h>
#include <UT/UT_Ramp.h>
#include <UT/UT_SharedPtr.h>
#include <UT/UT_StringHolder.h>
#include <UT/UT_StringStream.h>
#include <UT/UT_VectorTypes.h>
#include <UT/UT_EnvControl.h>
#include <SYS/SYS_Types.h>

using namespace UT::Literal;

class DEP_MicroNode;

class  SOP_importUSDParms  : public SOP_NodeParms
{
public:
    static int version() { return 1; }

    SOP_importUSDParms()
    {
        myUsdfile = "0"_sh;

    }

    explicit SOP_importUSDParms(const SOP_importUSDParms &) = default;

    ~SOP_importUSDParms() override {}

    bool operator==(const SOP_importUSDParms &src) const
    {
        if (myUsdfile != src.myUsdfile) return false;

        return true;
    }
    bool operator!=(const SOP_importUSDParms &src) const
    {
        return !operator==(src);
    }



    void        buildFromOp(const SOP_GraphProxy *graph, exint nodeidx, fpreal time, DEP_MicroNode *depnode)
    {
        myUsdfile = "0"_sh;
        if (true)
            graph->evalOpParm(myUsdfile, nodeidx, "usdFile", time, 0);

    }


    void loadFromOpSubclass(const LoadParms &loadparms) override
    {
        buildFromOp(loadparms.graph(), loadparms.nodeIdx(), loadparms.context().getTime(), loadparms.depnode());
    }


    void copyFrom(const SOP_NodeParms *src) override
    {
        *this = *((const SOP_importUSDParms *)src);
    }

    template <typename T>
    void
    doGetParmValue(TempIndex idx, TempIndex instance, T &value) const
    {
        if (idx.size() < 1)
            return;
        UT_ASSERT(idx.size() == instance.size()+1);
        if (idx.size() != instance.size()+1)
            return;
        switch (idx[0])
        {
            case 0:
                coerceValue(value, myUsdfile);
                break;

        }
    }

    void getNestParmValue(TempIndex idx, TempIndex instance, exint &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, fpreal &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector2D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector3D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Vector4D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix2D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix3D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_Matrix4D &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_StringHolder &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, UT_SharedPtr<UT_Ramp> &value) const override
    { doGetParmValue(idx, instance, value); }
    void getNestParmValue(TempIndex idx, TempIndex instance, PRM_DataItemHandle &value) const override
    { doGetParmValue(idx, instance, value); }

    template <typename T>
    void
    doSetParmValue(TempIndex idx, TempIndex instance, const T &value) 
    {
        if (idx.size() < 1)
            return;
        UT_ASSERT(idx.size() == instance.size()+1);
        if (idx.size() != instance.size()+1)
            return;
        switch (idx[0])
        {
            case 0:
                coerceValue(myUsdfile, ( ( value ) ));
                break;

        }
    }

    void setNestParmValue(TempIndex idx, TempIndex instance, const exint &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const fpreal &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector2D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector3D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Vector4D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix2D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix3D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_Matrix4D &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_StringHolder &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const UT_SharedPtr<UT_Ramp> &value)  override
    { doSetParmValue(idx, instance, value); }
    void setNestParmValue(TempIndex idx, TempIndex instance, const PRM_DataItemHandle &value)  override
    { doSetParmValue(idx, instance, value); }

    exint getNestNumParms(TempIndex idx) const override
    {
        if (idx.size() == 0)
            return 1;
        switch (idx[0])
        {

        }
        // Invalid
        return 0;
    }

    const char *getNestParmName(TempIndex fieldnum) const override
    {
        if (fieldnum.size() < 1)
            return 0;
        switch (fieldnum[0])
        {
            case 0:
                return "usdFile";

        }
        return 0;
    }

    ParmType getNestParmType(TempIndex fieldnum) const override
    {
        if (fieldnum.size() < 1)
            return PARM_UNSUPPORTED;
        switch (fieldnum[0])
        {
            case 0:
                return PARM_STRING;

        }
        return PARM_UNSUPPORTED;
    }

    // Boiler plate to load individual types.
    static void  loadData(UT_IStream &is, int64 &v)
    { is.bread(&v, 1); }
    static void  loadData(UT_IStream &is, bool &v)
    { int64     iv; is.bread(&iv, 1); v = iv; }
    static void  loadData(UT_IStream &is, fpreal64 &v)
    { is.bread<fpreal64>(&v, 1); }
    static void  loadData(UT_IStream &is, UT_Vector2D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector3D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1);
      is.bread<fpreal64>(&v.z(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector4D &v)
    { is.bread<fpreal64>(&v.x(), 1); is.bread<fpreal64>(&v.y(), 1);
      is.bread<fpreal64>(&v.z(), 1); is.bread<fpreal64>(&v.w(), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix2D &v)
    { for (int r = 0; r < 2; r++) for (int c = 0; c < 2; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix3D &v)
    { for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Matrix4D &v)
    { for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) is.bread<fpreal64>(&v(r, c), 1); }
    static void  loadData(UT_IStream &is, UT_Vector2I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector3I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1);
      is.bread<int64>(&v.z(), 1); }
    static void  loadData(UT_IStream &is, UT_Vector4I &v)
    { is.bread<int64>(&v.x(), 1); is.bread<int64>(&v.y(), 1);
      is.bread<int64>(&v.z(), 1); is.bread<int64>(&v.w(), 1); }
    static void  loadData(UT_IStream &is, UT_StringHolder &v)
    { is.bread(v); }
    static void  loadData(UT_IStream &is, UT_SharedPtr<UT_Ramp> &v)
    {   UT_StringHolder   rampdata;
        loadData(is, rampdata);
        if (rampdata.isstring())
        {
            v.reset(new UT_Ramp());
            UT_IStream  istr((const char *) rampdata, rampdata.length(), UT_ISTREAM_ASCII);
            v->load(istr);
        }
        else v.reset();
    }
    static void  loadData(UT_IStream &is, PRM_DataItemHandle &v)
    {   UT_StringHolder   data;
        loadData(is, data);
        if (data.isstring())
        {
            // Find the data type.
            const char *colon = UT_StringWrap(data).findChar(':');
            if (colon)
            {
                int             typelen = colon - data.buffer();
                UT_WorkBuffer   type;
                type.strncpy(data.buffer(), typelen);
                UT_IStream  istr(((const char *) data) + typelen + 1, data.length() - (typelen + 1), UT_ISTREAM_BINARY);
                
                v = PRM_DataFactory::parseBinary(type.buffer(), istr);
            }
        }
        else v.reset();
    }

    static void  saveData(std::ostream &os, int64 v)
    { UTwrite(os, &v); }
    static void  saveData(std::ostream &os, bool v)
    { int64 iv = v; UTwrite(os, &iv); }
    static void  saveData(std::ostream &os, fpreal64 v)
    { UTwrite<fpreal64>(os, &v); }
    static void  saveData(std::ostream &os, UT_Vector2D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y()); }
    static void  saveData(std::ostream &os, UT_Vector3D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y());
      UTwrite<fpreal64>(os, &v.z()); }
    static void  saveData(std::ostream &os, UT_Vector4D v)
    { UTwrite<fpreal64>(os, &v.x()); UTwrite<fpreal64>(os, &v.y());
      UTwrite<fpreal64>(os, &v.z()); UTwrite<fpreal64>(os, &v.w()); }
    static void  saveData(std::ostream &os, UT_Matrix2D v)
    { for (int r = 0; r < 2; r++) for (int c = 0; c < 2; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_Matrix3D v)
    { for (int r = 0; r < 3; r++) for (int c = 0; c < 3; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_Matrix4D v)
    { for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) UTwrite<fpreal64>(os, &v(r, c)); }
    static void  saveData(std::ostream &os, UT_StringHolder s)
    { UT_StringWrap(s).saveBinary(os); }
    static void  saveData(std::ostream &os, UT_SharedPtr<UT_Ramp> s)
    {   UT_StringHolder         result;
        UT_OStringStream        ostr;
        if (s) s->save(ostr);
        result = ostr.str();
        saveData(os, result);
    }
    static void  saveData(std::ostream &os, PRM_DataItemHandle s)
    {   UT_StringHolder         result;
        UT_OStringStream        ostr;
        if (s) 
        {
            ostr << s->getDataTypeToken();
            ostr << ":";
            s->saveBinary(ostr);
        }
        result = ostr.str();
        saveData(os, result);
    }


    void         save(std::ostream &os) const
    {
        int32           v = version();
        UTwrite(os, &v);
        saveData(os, myUsdfile);

    }

    bool         load(UT_IStream &is)
    {
        int32           v;
        is.bread(&v, 1);
        if (version() != v)
        {
            // Fail incompatible versions
            return false;
        }
        loadData(is, myUsdfile);

        return true;
    }

    const UT_StringHolder & getUsdfile() const { return myUsdfile; }
    void setUsdfile(const UT_StringHolder & val) { myUsdfile = val; }
    UT_StringHolder opUsdfile(const SOP_NodeVerb::CookParms &cookparms) const
    { 
        SOP_Node *thissop = cookparms.getNode();
        if (!thissop) return getUsdfile();
        UT_StringHolder result;
        OP_Utils::evalOpParm(result, thissop, "usdFile", cookparms.getCookTime(), 0);
        return result;
    }

private:
    UT_StringHolder myUsdfile;

};
