#include <QRegularExpression>
#include <QTextStream>

QTextStream out(stdout, QIODevice::WriteOnly);
QTextStream in(stdin, QIODevice::ReadOnly);

enum Base
{
    Oct = 8, Dec = 10, Hex = 16
};

QString repr(Base base)
{
    switch (base)
    {
    case Oct: return QString("oct");
    case Dec: return QString("dec");
    case Hex: return QString("hex");
    default:  return QString("???");
    }
}

Base baseOf(QString s)
{
    QRegularExpression re("[ABCDEF]");
    if (s.startsWith("0x") || s.contains(re) || s.endsWith("h"))
        return Base::Hex;
    else if (s.startsWith('0'))
        return Base::Oct;
    else
        return Base::Dec;
}

int main(int argc, char **argv)
{
    QString input;
    if (argc < 2)
    {
        out << "hex/dec/oct: ";
        out.flush();

        in >> input;
    }
    else
        input = QString(argv[1]);

    bool ok;
    Base base = baseOf(input);
    long dec = input.toLong(&ok, base);
    if (!ok)
    {
        out << "Not a number." << endl;
        return 1;
    }

    out << "IN: " << repr(base) << ": " << input << endl;

    QString hex = QString::number(dec, 16).toUpper();
    QString oct = QString::number(dec, 8);

    out << "hex: " << hex << endl
        << "dec: " << dec << endl
        << "oct: " << oct << endl;

    return 0;
}
